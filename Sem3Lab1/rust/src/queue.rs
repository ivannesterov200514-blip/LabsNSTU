use crate::node::Node;
use std::ptr;

pub struct Queue {
    head: Option<Box<Node>>,
    tail: *mut Node,
    sz: i32,
}

impl Default for Queue {
    fn default() -> Queue {
        Queue { head: None, tail: ptr::null_mut(), sz: 0 }
    }
}

impl Drop for Queue {
    fn drop(&mut self) {
        let mut cur = self.head.take();
        while let Some(mut node) = cur {
            cur = node.next.take();
        }
    }
}

impl Queue {
    pub fn push(&mut self, val: &str) {
        let mut n = Box::new(Node { data: val.to_string(), next: None });
        let raw: *mut Node = &mut *n;
        if self.tail.is_null() {
            self.head = Some(n);
        } else {
            unsafe {
                (*self.tail).next = Some(n);
            }
        }
        self.tail = raw;
        self.sz += 1;
    }

    pub fn pop(&mut self) {
        match self.head.take() {
            None => println!("Ошибка: Очередь пуста"),
            Some(v) => {
                println!("{}", v.data);
                self.head = v.next;
                if self.head.is_none() {
                    self.tail = ptr::null_mut();
                }
                self.sz -= 1;
            }
        }
    }

    pub fn print(&self) {
        if self.head.is_none() {
            println!("Очередь пуста");
            return;
        }
        print!("Head: ");
        let mut cur = self.head.as_deref();
        while let Some(n) = cur {
            print!("{} -> ", n.data);
            cur = n.next.as_deref();
        }
        println!(": Tail");
    }

    pub fn values(&self) -> Vec<String> {
        let mut v = Vec::new();
        let mut cur = self.head.as_deref();
        while let Some(n) = cur {
            v.push(n.data.clone());
            cur = n.next.as_deref();
        }
        v
    }
}
