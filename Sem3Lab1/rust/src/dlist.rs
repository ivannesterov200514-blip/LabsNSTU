use std::cell::RefCell;
use std::rc::{Rc, Weak};

type Link = Option<Rc<RefCell<SNode>>>;

struct SNode {
    data: String,
    next: Link,
    prev: Option<Weak<RefCell<SNode>>>,
}

fn new_node(data: &str, next: Link, prev: Option<Weak<RefCell<SNode>>>) -> Rc<RefCell<SNode>> {
    Rc::new(RefCell::new(SNode { data: data.to_string(), next, prev }))
}

#[derive(Default)]
pub struct DList {
    head: Link,
    sz: i32,
}

impl Drop for DList {
    fn drop(&mut self) {
        let mut cur = self.head.take();
        while let Some(node) = cur {
            cur = node.borrow_mut().next.take();
        }
    }
}

impl DList {
    fn find(&self, key: &str) -> Link {
        let mut cur = self.head.clone();
        while let Some(node) = cur {
            if node.borrow().data == key {
                return Some(node);
            }
            cur = node.borrow().next.clone();
        }
        None
    }

    fn last(&self) -> Link {
        let mut cur = self.head.clone()?;
        loop {
            let next = cur.borrow().next.clone();
            match next {
                Some(n) => cur = n,
                None => return Some(cur),
            }
        }
    }

    fn unlink(&mut self, v: &Rc<RefCell<SNode>>) {
        let prev: Link = v.borrow().prev.as_ref().and_then(|w| w.upgrade());
        let next: Link = v.borrow_mut().next.take();
        match &prev {
            Some(p) => p.borrow_mut().next = next.clone(),
            None => self.head = next.clone(),
        }
        if let Some(nx) = &next {
            nx.borrow_mut().prev = prev.as_ref().map(Rc::downgrade);
        }
        self.sz -= 1;
    }

    pub fn insert_head(&mut self, val: &str) {
        let n = new_node(val, self.head.clone(), None);
        if let Some(h) = &self.head {
            h.borrow_mut().prev = Some(Rc::downgrade(&n));
        }
        self.head = Some(n);
        self.sz += 1;
    }

    pub fn insert_tail(&mut self, val: &str) {
        match self.last() {
            None => {
                self.head = Some(new_node(val, None, None));
            }
            Some(last) => {
                let n = new_node(val, None, Some(Rc::downgrade(&last)));
                last.borrow_mut().next = Some(n);
            }
        }
        self.sz += 1;
    }

    pub fn insert_before(&mut self, key: &str, val: &str) {
        let cur = match self.find(key) {
            Some(c) => c,
            None => {
                println!("Ошибка: Не найдено");
                return;
            }
        };
        let prev: Link = cur.borrow().prev.as_ref().and_then(|w| w.upgrade());
        let n = new_node(val, Some(cur.clone()), prev.as_ref().map(Rc::downgrade));
        match &prev {
            Some(p) => p.borrow_mut().next = Some(n.clone()),
            None => self.head = Some(n.clone()),
        }
        cur.borrow_mut().prev = Some(Rc::downgrade(&n));
        self.sz += 1;
    }

    pub fn insert_after(&mut self, key: &str, val: &str) {
        let cur = match self.find(key) {
            Some(c) => c,
            None => {
                println!("Ошибка: Не найдено");
                return;
            }
        };
        let next: Link = cur.borrow().next.clone();
        let n = new_node(val, next.clone(), Some(Rc::downgrade(&cur)));
        if let Some(nx) = &next {
            nx.borrow_mut().prev = Some(Rc::downgrade(&n));
        }
        cur.borrow_mut().next = Some(n);
        self.sz += 1;
    }

    pub fn delete_head(&mut self) {
        let h = match self.head.clone() {
            Some(h) => h,
            None => {
                println!("Ошибка: Список пуст");
                return;
            }
        };
        if h.borrow().next.is_none() {
            println!("Последний узел списка удален.");
        }
        self.unlink(&h);
    }

    pub fn delete_tail(&mut self) {
        let last = match self.last() {
            Some(l) => l,
            None => {
                println!("Ошибка: Список пуст");
                return;
            }
        };
        if last.borrow().prev.is_none() {
            println!("Последний узел списка удален.");
        }
        self.unlink(&last);
    }

    pub fn delete_before(&mut self, key: &str) {
        let cur = match self.find(key) {
            Some(c) => c,
            None => {
                println!("Ошибка: Не найдено");
                return;
            }
        };
        let prev: Link = cur.borrow().prev.as_ref().and_then(|w| w.upgrade());
        match prev {
            None => println!("Ошибка: Перед элементом ничего нет"),
            Some(p) => self.unlink(&p),
        }
    }

    pub fn delete_after(&mut self, key: &str) {
        let cur = match self.find(key) {
            Some(c) => c,
            None => {
                println!("Ошибка: Не найдено");
                return;
            }
        };
        let next: Link = cur.borrow().next.clone();
        match next {
            None => println!("Ошибка: После элемента ничего нет"),
            Some(nx) => self.unlink(&nx),
        }
    }

    pub fn delete_key(&mut self, key: &str) {
        let cur = match self.find(key) {
            Some(c) => c,
            None => {
                println!("Ошибка: Не найдено");
                return;
            }
        };
        let single = match &self.head {
            Some(h) => h.borrow().next.is_none(),
            None => false,
        };
        if single {
            println!("Последний узел списка удален.");
        }
        self.unlink(&cur);
    }

    pub fn search(&self, key: &str) -> String {
        match self.find(key) {
            None => {
                println!("Ошибка: Не найдено");
                String::new()
            }
            Some(n) => {
                let d = n.borrow().data.clone();
                println!("{}", d);
                d
            }
        }
    }

    pub fn print_iter(&self) {
        if self.head.is_none() {
            println!("Список пуст");
            return;
        }
        print!("nullptr <-> ");
        let mut cur = self.head.clone();
        while let Some(n) = cur {
            print!("{} <-> ", n.borrow().data);
            cur = n.borrow().next.clone();
        }
        println!("nullptr");
    }

    pub fn print_rec(&self) {
        if self.head.is_none() {
            println!("Список пуст");
            return;
        }
        print!("nullptr <-> ");
        print_recurs(&self.head);
    }

    pub fn values(&self) -> Vec<String> {
        let mut v = Vec::new();
        let mut cur = self.head.clone();
        while let Some(n) = cur {
            v.push(n.borrow().data.clone());
            cur = n.borrow().next.clone();
        }
        v
    }
}

fn print_recurs(c: &Link) {
    match c {
        None => println!("nullptr"),
        Some(n) => {
            let node = n.borrow();
            print!("{} <-> ", node.data);
            print_recurs(&node.next);
        }
    }
}
