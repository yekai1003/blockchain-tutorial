/*
 * @CopyRight:
 * FISCO-BCOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FISCO-BCOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FISCO-BCOS.  If not, see <http://www.gnu.org/licenses/>
 * (c) 2016-2018 fisco-dev contributors.
 */
/** @file CounterPrecompiled.cpp
 *  @author yekai
 *  @date 20221118
 */
#include "CounterPrecompiled.h"
#include <libblockverifier/ExecutiveContext.h>
#include <libethcore/ABI.h>
#include <libprecompiled/TableFactoryPrecompiled.h>

using namespace dev;
using namespace dev::blockverifier;
using namespace dev::storage;
using namespace dev::precompiled;

/*
interface  CounterPrecompiled {
    function init(address _keyAddr) external;
    function increment(address _keyAddr) external;
    function incrementBy(address _keyAddr, uint256 _value) external;
    function reset(address _keyAddr) external;
    function get(address _keyAddr) external view returns(uint256);
}
*/


// CounterPrecompiled table name
const std::string COUNTER_TABLE_NAME = "counter";
// key field
const std::string COUNTER_KEY_FIELD = "key";
//const std::string COUNTER_KEY_FIELD_NAME = "hello_key";
// value field
const std::string COUNTER_VALUE_FIELD = "value";

// get interface
const char* const COUNTER_METHOD_GET = "get(string)";
// init interface
const char* const COUNTER_METHOD_INIT = "init(string)";
// reset interface
const char* const COUNTER_METHOD_RESET = "reset(string)";
// increment interface
const char* const COUNTER_METHOD_INRC = "increment(string)";
// incrementBy interface
const char* const COUNTER_METHOD_INRC_BY = "incrementBy(string)";


CounterPrecompiled::CounterPrecompiled()
{
    name2Selector[COUNTER_METHOD_GET] = getFuncSelector(COUNTER_METHOD_GET);
    name2Selector[COUNTER_METHOD_INIT] = getFuncSelector(COUNTER_METHOD_INIT);
    name2Selector[COUNTER_METHOD_RESET] = getFuncSelector(COUNTER_METHOD_RESET);
    name2Selector[COUNTER_METHOD_INRC] = getFuncSelector(COUNTER_METHOD_INRC);
    name2Selector[COUNTER_METHOD_INRC_BY] = getFuncSelector(COUNTER_METHOD_INRC_BY);
}

std::string CounterPrecompiled::toString()
{
    return "Counter";
}

PrecompiledExecResult::Ptr CounterPrecompiled::call(
    dev::blockverifier::ExecutiveContext::Ptr _context, bytesConstRef _param,
    Address const& _origin, Address const&)
{
    PRECOMPILED_LOG(TRACE) << LOG_BADGE("CounterPrecompiled") << LOG_DESC("call")
                           << LOG_KV("param", toHex(_param));

    // parse function name
    uint32_t func = getParamFunc(_param);
    bytesConstRef data = getParamData(_param);
    auto callResult = m_precompiledExecResultFactory->createPrecompiledResult();
    callResult->gasPricer()->setMemUsed(_param.size());
    dev::eth::ContractABI abi;

    Table::Ptr table = openTable(_context, precompiled::getTableName(COUNTER_TABLE_NAME));
    callResult->gasPricer()->appendOperation(InterfaceOpcode::OpenTable);
    if (!table)
    {
        // table is not exist, create it.
        table = createTable(_context, precompiled::getTableName(COUNTER_TABLE_NAME),
            COUNTER_KEY_FIELD, COUNTER_VALUE_FIELD, _origin);
        callResult->gasPricer()->appendOperation(InterfaceOpcode::CreateTable);
        if (!table)
        {
            PRECOMPILED_LOG(ERROR) << LOG_BADGE("CounterPrecompiled") << LOG_DESC("set")
                                   << LOG_DESC("open table failed.");
            getErrorCodeOut(callResult->mutableExecResult(), storage::CODE_NO_AUTHORIZED);
            return callResult;
        }
    }
    if (func == name2Selector[COUNTER_METHOD_GET])
    {  // get(string) func
        std::string keyName;
        abi.abiOut(data, keyName);
        std::string retValue = "0";
        
        auto entries = table->select(keyName, table->newCondition());
        if (0u != entries->size())
        {
            callResult->gasPricer()->updateMemUsed(getEntriesCapacity(entries));
            callResult->gasPricer()->appendOperation(InterfaceOpcode::Select, entries->size());
            auto entry = entries->get(0);
            retValue = entry->getField(COUNTER_VALUE_FIELD);
            PRECOMPILED_LOG(ERROR) << LOG_BADGE("CounterPrecompiled") << LOG_DESC("get")
                                   << LOG_KV("value", retValue);
        }
        callResult->setExecResult(abi.abiIn("", retValue));
    }
    else if (func == name2Selector[COUNTER_METHOD_INIT])
    {
        std::string strKey;
        std::string strValue = "0";
        abi.abiOut(data, strKey);
        auto entries = table->select(strKey, table->newCondition());
        if(0u != entries->size()) {
            PRECOMPILED_LOG(ERROR) << LOG_BADGE("CounterPrecompiled") << LOG_DESC("set")
                                   << LOG_DESC("key already exists.");
            getErrorCodeOut(callResult->mutableExecResult(), storage::CODE_NO_AUTHORIZED);
            return callResult;
        }
        // init要增加一条
        auto entry = table->newEntry();
        entry->setField(COUNTER_KEY_FIELD, strKey);
        entry->setField(COUNTER_VALUE_FIELD, strValue);

        count = table->insert(
                strKey, entry, std::make_shared<AccessOptions>(_origin));
        if (count > 0)
        {
            callResult->gasPricer()->updateMemUsed(entry->capacity() * count);
            callResult->gasPricer()->appendOperation(InterfaceOpcode::Insert, count);
        }

        if (count == storage::CODE_NO_AUTHORIZED)
        {  //  permission denied
            PRECOMPILED_LOG(ERROR) << LOG_BADGE("CounterPrecompiled") << LOG_DESC("set")
                                   << LOG_DESC("permission denied");
        }
        getErrorCodeOut(callResult->mutableExecResult(), count);

    }
    else if (func == name2Selector[COUNTER_METHOD_INRC])
    {  // inrc(string) function call

        std::string strValue;
        abi.abiOut(data, strValue);
        auto entries = table->select(HELLOWORLD_KEY_FIELD_NAME, table->newCondition());
        callResult->gasPricer()->updateMemUsed(getEntriesCapacity(entries));
        callResult->gasPricer()->appendOperation(InterfaceOpcode::Select, entries->size());

        auto entry = table->newEntry();
        entry->setField(HELLOWORLD_KEY_FIELD, HELLOWORLD_KEY_FIELD_NAME);
        entry->setField(HELLOWORLD_VALUE_FIELD, strValue);

        int count = 0;
        if (0u != entries->size())
        {  // update
            count = table->update(HELLOWORLD_KEY_FIELD_NAME, entry, table->newCondition(),
                std::make_shared<AccessOptions>(_origin));
            if (count > 0)
            {
                callResult->gasPricer()->appendOperation(InterfaceOpcode::Update, count);
                callResult->gasPricer()->updateMemUsed(entry->capacity() * count);
            }
        }
        else
        {  // insert
            count = table->insert(
                HELLOWORLD_KEY_FIELD_NAME, entry, std::make_shared<AccessOptions>(_origin));
            if (count > 0)
            {
                callResult->gasPricer()->updateMemUsed(entry->capacity() * count);
                callResult->gasPricer()->appendOperation(InterfaceOpcode::Insert, count);
            }
        }

        if (count == storage::CODE_NO_AUTHORIZED)
        {  //  permission denied
            PRECOMPILED_LOG(ERROR) << LOG_BADGE("HelloWorldPrecompiled") << LOG_DESC("set")
                                   << LOG_DESC("permission denied");
        }
        getErrorCodeOut(callResult->mutableExecResult(), count);
    }
    else
    {  // unknown function call
        PRECOMPILED_LOG(ERROR) << LOG_BADGE("HelloWorldPrecompiled") << LOG_DESC(" unknown func ")
                               << LOG_KV("func", func);
        callResult->setExecResult(abi.abiIn("", u256(int32_t(CODE_UNKNOW_FUNCTION_CALL))));
    }

    return callResult;
}
