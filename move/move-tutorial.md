```move
module Yekai::Math2 {
    const A1:address = @0x1;
    public fun sum(a:u64, b: u8) :u64 {
         a + (b as u64)
    }
    public fun max(a:u64, b:u64) :u64 {
        if(a > b) {
            a
        } else {
            b
        }

    }
}

module Std::Stdmod {
    public fun get_addr() :address {
        let a1:address = @Std;
        a1
    }
}

script {
    use 0x1::Debug; /// import other module
    use 0x2::Math2;
    //const A1:address = @0x1;
    let b1:address = @0x1;
    const A1:address = @0x1;
    /// main just a name 
    fun main() {
        let num:u64 = 1024;
        let a1:address = @0x1;
        Debug::print(&num);
        num = Math2::sum(10, 20);
        Debug::print(&num);
        let addr1:address = @Yekai;
        Debug::print(&addr1);
        Debug::print(&Math2::max(10,20));
    }
}


```

http://www.codebaoku.com/move/move-abort.html

move教程

https://github.com/move-dao/move-book-zh/blob/main/src/abort-and-assert.md



### 引用



```js
module 0x1::Math {
    public fun swap(a: &mut u64, b: &mut u64) {
        let temp = *a ;
        *a = *b;
        *b = temp;
    }
}

script {
    use 0x1::Math;
    use 0x1::Debug;
    fun test_main() {
        let (a,b) = (10,20);
        let (a,b) = (30,40);
        Math::swap(&mut a, &mut b);
        Debug::print(&a);
        Debug::print(&b);
    }
    
}
```



### 泛型结构



```js
address Sender {
    module student{
        
        struct User<T1, T2> has drop, copy{
            id: T1,
            age: T2
        }

        public fun new_student<T1 , T2>(id:T1, age:T2): User<T1, T2> {
            User{id, age}
        }
    }


}
```



### 所有权



```js
module 0x1::Math { 
    use 0x1::Debug;
    public fun max(a: u64, b: u64) :u64 { 
        if(a >= b) {  
            a 
        } else { 
            b 
        } 
    } 
 
    public fun max2(a: u8, b: u8) :u8 { 
        if(a >= b) {  
            a 
        } else { 
            b 
        } 
    } 
    /* 
    public fun max3<T>(a: T, b: T) :T { 
        if(a >= b) {  
            a 
        } else { 
            b 
        } 
    }*/ 

    public fun show(x:u64) {
        Debug::print(&x);
    }
 
}


```



### signer

`signer` 是Move内置的资源类型。`signer` 是一种允许持有者代表特定 `address` 行使权力的能力([capability](https://en.wikipedia.org/wiki/Object-capability_model))

你可以将原生实现(native implementation)视为：

```move
struct signer has drop { a: address }
```

`signer` 有点像Unix [UID](https://en.wikipedia.org/wiki/User_identifier), 它表示一个在 Move 代码之外(**outside**)进行身份验证的用户(例如通过检查加密签名或密码)。

Move程序可以使用地址字面值(literals)在没有特殊许可的情况下创建 `address` 值。

```
let a1 = @0x1;
let a2 = @0x2;
// ... and so on for every other possible address
```

但是，`signer` 值是特殊的，因为它们不能通过字面值(literals)或者指令创建--只能通过Move虚拟机(VM)。 在虚拟机(VM)运行带有 `signer` 类型参数的脚本之前，它将自动创建 `signer` 值并将它们传递到脚本中：

```
script {
    use std::signer;
    fun main(s: signer) {
        assert!(signer::address_of(&s) == @0x42, 0);
    }
}
```

如果脚本是从 `0x42` 以外的任务地址发送的，则此脚本将中止并返回代码 `0`。

脚本可以有任意数量的 `signer`, 只要 `signer` 参数排在其他参数前面。换句话说，所有 `signer` 参数都必须放在第一位。

```
script {
    use std::signer;
    fun main(s1: signer, s2: signer, x: u64, y: u8) {
        // ...
    }
}
```

这对于实现具有多方权限原子行为的多签名脚本(*multi-signer scripts*)很有用。 例如，上述脚本的扩展可以在 `s1` 和 `s2` 之间执行原子货币交换。



### 面向资源编程

```js
// modules/Collection.move
module 0x1::collection {

    use 0x1::Vector;
    use 0x1::Signer;


    struct Item has store,drop {}

    struct Collection has key {
        items: vector<Item>
    }

     /// note that &signer type is passed here!
    public fun start_collection(account: &signer) {
       move_to<Collection>(account, Collection {
            items: Vector::empty<Item>()
        }) 
    }

    public fun exists_at(at: address): bool {
        exists<Collection>(at)
    }
    

    public fun size(account: &signer): u64 acquires Collection {
        let owner = Signer::address_of(account);
        let collection = borrow_global<Collection>(owner);

        Vector::length(&collection.items)
    }

    public fun add_item(account: &signer) acquires Collection  {
        let collection = borrow_global_mut<Collection>(Signer::address_of(account));

        Vector::push_back(&mut collection.items, Item {});
    }

    public fun destroy(account: &signer) acquires Collection {

        // account no longer has resource attached
        let collection = move_from<Collection>(Signer::address_of(account));

        // now we must use resource value - we'll destructure it
        // look carefully - Items must have drop ability
        let Collection { items: _ } = collection;

        // done. resource destroyed
    }
}
```


