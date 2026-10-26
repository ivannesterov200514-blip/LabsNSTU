use crate::node::Node;

#[derive(Default)]
pub struct UList {
    head: Option<Box<Node>>,
    sz: i32,
}

impl Drop for UList {
    fn drop(&mut self) {
        let mut cur = self.head.take();
        while let Some(mut node) = cur {
            cur = node.next.take();
        }
    }
}

impl UList {
    fn find_mut(&mut self, key: &str) -> Option<&mut Node> {
        let mut cur = self.head.as_deref_mut();
        while let Some(node) = cur {
            if node.data == key {
                return Some(node);
            }
            cur = node.next.as_deref_mut();
        }
        None
    }

    fn pop_head(&mut self) {
        if let Some(old) = self.head.take() {
            self.head = old.next;
            self.sz -= 1;
        }
    }

    pub fn insert_head(&mut self, val: &str) {
        let n = Box::new(Node { data: val.to_string(), next: self.head.take() });
        self.head = Some(n);
        self.sz += 1;
    }

    pub fn insert_tail(&mut self, val: &str) {
        let n = Box::new(Node { data: val.to_string(), next: None });
        let mut link = &mut self.head;
        while link.is_some() {
            link = &mut link.as_mut().unwrap().next;
        }
        *link = Some(n);
        self.sz += 1;
    }

    pub fn insert_before(&mut self, key: &str, val: &str) {
        let mut link = &mut self.head;
        while link.as_ref().map_or(false, |n| n.data != key) {
            link = &mut link.as_mut().unwrap().next;
        }
        if link.is_none() {
            println!("Ошибка: Не найдено");
            return;
        }
        let n = Box::new(Node { data: val.to_string(), next: link.take() });
        *link = Some(n);
        self.sz += 1;
    }

    pub fn insert_after(&mut self, key: &str, val: &str) {
        let found = match self.find_mut(key) {
            Some(cur) => {
                let n = Box::new(Node { data: val.to_string(), next: cur.next.take() });
                cur.next = Some(n);
                true
            }
            None => false,
        };
        if found {
            self.sz += 1;
        } else {
            println!("Ошибка: Не найдено");
        }
    }

    pub fn delete_head(&mut self) {
        if self.head.is_none() {
            println!("Ошибка: Список пуст");
            return;
        }
        if self.head.as_ref().unwrap().next.is_none() {
            println!("Последний узел списка удален.");
        }
        self.pop_head();
    }

    pub fn delete_tail(&mut self) {
        if self.head.is_none() {
            println!("Ошибка: Список пуст");
            return;
        }
        if self.head.as_ref().unwrap().next.is_none() {
            self.head = None;
            self.sz -= 1;
            println!("Последний узел списка удален.");
            return;
        }
        let mut cur = self.head.as_mut().unwrap();
        while cur.next.as_ref().unwrap().next.is_some() {
            cur = cur.next.as_mut().unwrap();
        }
        cur.next = None;
        self.sz -= 1;
    }

    pub fn delete_before(&mut self, key: &str) {
        if self.head.is_none() || self.head.as_ref().unwrap().next.is_none() {
            println!("Ошибка: Не найдено");
            return;
        }
        if self.head.as_ref().unwrap().data == key {
            println!("Ошибка: Перед элементом ничего нет");
            return;
        }
        if self.head.as_ref().unwrap().next.as_ref().unwrap().data == key {
            self.pop_head();
            return;
        }
        let mut cur = self.head.as_mut().unwrap();
        while cur
            .next
            .as_ref()
            .map_or(false, |n| n.next.as_ref().map_or(false, |nn| nn.data != key))
        {
            cur = cur.next.as_mut().unwrap();
        }
        let found = cur.next.as_ref().map_or(false, |n| n.next.is_some());
        if !found {
            println!("Ошибка: Не найдено");
            return;
        }
        let victim = cur.next.take().unwrap();
        cur.next = victim.next;
        self.sz -= 1;
    }

    pub fn delete_after(&mut self, key: &str) {
        let state = match self.find_mut(key) {
            None => 0,
            Some(cur) => match cur.next.take() {
                None => 1,
                Some(v) => {
                    cur.next = v.next;
                    2
                }
            },
        };
        match state {
            0 => println!("Ошибка: Не найдено"),
            1 => println!("Ошибка: После элемента ничего нет"),
            _ => self.sz -= 1,
        }
    }

    pub fn delete_key(&mut self, key: &str) {
        if self.head.is_none() {
            println!("Ошибка: Не найдено");
            return;
        }
        if self.head.as_ref().unwrap().data == key {
            if self.head.as_ref().unwrap().next.is_none() {
                println!("Последний узел списка удален.");
            }
            self.pop_head();
            return;
        }
        let mut cur = self.head.as_mut().unwrap();
        while cur.next.as_ref().map_or(false, |n| n.data != key) {
            cur = cur.next.as_mut().unwrap();
        }
        match cur.next.take() {
            None => println!("Ошибка: Не найдено"),
            Some(v) => {
                cur.next = v.next;
                self.sz -= 1;
            }
        }
    }

    pub fn search(&self, key: &str) -> String {
        let mut cur = self.head.as_deref();
        while let Some(n) = cur {
            if n.data == key {
                println!("{}", n.data);
                return n.data.clone();
            }
            cur = n.next.as_deref();
        }
        println!("Ошибка: Не найдено");
        String::new()
    }

    pub fn print_iter(&self) {
        if self.head.is_none() {
            println!("Список пуст");
            return;
        }
        let mut cur = self.head.as_deref();
        while let Some(n) = cur {
            print!("{} -> ", n.data);
            cur = n.next.as_deref();
        }
        println!("nullptr");
    }

    pub fn print_rec(&self) {
        if self.head.is_none() {
            println!("Список пуст");
            return;
        }
        print_recurs(&self.head);
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

fn print_recurs(c: &Option<Box<Node>>) {
    match c {
        None => println!("nullptr"),
        Some(n) => {
            print!("{} -> ", n.data);
            print_recurs(&n.next);
        }
    }
}
