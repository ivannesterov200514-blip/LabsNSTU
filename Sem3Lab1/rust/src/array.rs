use std::mem;

pub struct Arr {
    data: Box<[String]>,
    size: i32,
    capacity: i32,
}

fn make_buf(cap: i32) -> Box<[String]> {
    vec![String::new(); cap as usize].into_boxed_slice()
}

impl Default for Arr {
    fn default() -> Arr {
        Arr::new(2)
    }
}

impl Arr {
    pub fn new(cap: i32) -> Arr {
        let capacity = if cap > 0 { cap } else { 2 };
        Arr { data: make_buf(capacity), size: 0, capacity }
    }

    fn resize(&mut self, newcap: i32) {
        let mut newdata = make_buf(newcap);
        for i in 0..self.size as usize {
            newdata[i] = mem::take(&mut self.data[i]);
        }
        self.data = newdata;
        self.capacity = newcap;
    }

    pub fn search(&self, idx: i32) -> String {
        if idx >= self.size || idx < 0 {
            println!("Ошибка: Такого индекса нет");
            return String::new();
        }
        self.data[idx as usize].clone()
    }

    pub fn insert_tail(&mut self, val: &str) {
        if self.size >= self.capacity {
            self.resize(self.capacity * 2);
        }
        self.data[self.size as usize] = val.to_string();
        self.size += 1;
    }

    pub fn insert_idx(&mut self, val: &str, idx: i32) {
        if idx > self.size || idx < 0 {
            println!("Ошибка: Такого индекса нет");
            return;
        }
        if self.size >= self.capacity {
            self.resize(self.capacity * 2);
        }
        let mut i = self.size as usize;
        while i > idx as usize {
            self.data[i] = mem::take(&mut self.data[i - 1]);
            i -= 1;
        }
        self.data[idx as usize] = val.to_string();
        self.size += 1;
    }

    pub fn delete_idx(&mut self, idx: i32) {
        if idx >= self.size || idx < 0 {
            println!("Ошибка: Такого индекса нет");
            return;
        }
        let last = self.size as usize - 1;
        let mut i = idx as usize;
        while i < last {
            self.data[i] = mem::take(&mut self.data[i + 1]);
            i += 1;
        }
        self.data[last] = String::new();
        self.size -= 1;
    }

    pub fn change_idx(&mut self, val: &str, idx: i32) {
        if idx >= self.size || idx < 0 {
            println!("Ошибка: Такого индекса нет");
            return;
        }
        self.data[idx as usize] = val.to_string();
    }

    pub fn size(&self) -> i32 {
        self.size
    }

    pub fn print(&self) {
        print!("Массив: ");
        for i in 0..self.size as usize {
            print!("{} ", self.data[i]);
        }
        println!();
    }

    pub fn values(&self) -> Vec<String> {
        self.data[..self.size as usize].to_vec()
    }
}
