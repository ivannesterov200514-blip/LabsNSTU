use crate::node::Node;

#[derive(Default)]
pub struct Stack {
    top: Option<Box<Node>>,
    sz: i32,
}

impl Drop for Stack {
    fn drop(&mut self) {
        let mut cur = self.top.take();
        while let Some(mut node) = cur {
            cur = node.next.take();
        }
    }
}

impl Stack {
    pub fn push(&mut self, val: &str) {
        let n = Box::new(Node { data: val.to_string(), next: self.top.take() });
        self.top = Some(n);
        self.sz += 1;
    }

    pub fn pop(&mut self) {
        match self.top.take() {
            None => println!("Ошибка: Стек пуст"),
            Some(v) => {
                println!("{}", v.data);
                self.top = v.next;
                self.sz -= 1;
            }
        }
    }

    pub fn print(&self) {
        if self.top.is_none() {
            println!("Стек пуст");
            return;
        }
        let mut cur = self.top.as_deref();
        while let Some(n) = cur {
            println!("{}", n.data);
            cur = n.next.as_deref();
        }
        println!("nullptr");
    }

    pub fn values(&self) -> Vec<String> {
        let mut v = Vec::new();
        let mut cur = self.top.as_deref();
        while let Some(n) = cur {
            v.push(n.data.clone());
            cur = n.next.as_deref();
        }
        v
    }
}
