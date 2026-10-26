#![allow(dead_code)]

mod array;
mod dlist;
mod node;
mod queue;
mod stack;
mod ulist;

use array::Arr;
use dlist::DList;
use queue::Queue;
use stack::Stack;
use std::collections::BTreeMap;
use std::fs;
use ulist::UList;

#[derive(Default)]
struct Db {
    arrs: BTreeMap<String, Arr>,
    uls: BTreeMap<String, UList>,
    dls: BTreeMap<String, DList>,
    sts: BTreeMap<String, Stack>,
    qs: BTreeMap<String, Queue>,
    types: BTreeMap<String, char>,
}

fn find_cont<'a, T>(map: &'a mut BTreeMap<String, T>, name: &str) -> Option<&'a mut T> {
    let r = map.get_mut(name);
    if r.is_none() {
        println!("Ошибка: Контейнер {} не найден", name);
    }
    r
}

fn get_or_create<'a, T: Default>(
    map: &'a mut BTreeMap<String, T>,
    types: &mut BTreeMap<String, char>,
    name: &str,
    ty: char,
) -> Option<&'a mut T> {
    if let Some(&t) = types.get(name) {
        if t != ty {
            println!("Ошибка: Имя {} уже занято другой структурой", name);
            return None;
        }
    }
    types.insert(name.to_string(), ty);
    Some(map.entry(name.to_string()).or_default())
}

fn to_int(s: &str) -> Option<i32> {
    match s.parse::<i32>() {
        Ok(x) => Some(x),
        Err(_) => {
            println!("Ошибка: Индекс должен быть числом");
            None
        }
    }
}

fn push_line(out: &mut String, ty: char, name: &str, vals: &[String]) {
    out.push(ty);
    out.push(' ');
    out.push_str(name);
    for v in vals {
        out.push(' ');
        out.push_str(v);
    }
    out.push('\n');
}

fn save_db(db: &Db, file: &str) {
    let mut out = String::new();
    for (name, c) in &db.arrs {
        push_line(&mut out, 'M', name, &c.values());
    }
    for (name, c) in &db.uls {
        push_line(&mut out, 'F', name, &c.values());
    }
    for (name, c) in &db.dls {
        push_line(&mut out, 'L', name, &c.values());
    }
    for (name, c) in &db.sts {
        push_line(&mut out, 'S', name, &c.values());
    }
    for (name, c) in &db.qs {
        push_line(&mut out, 'Q', name, &c.values());
    }
    if fs::write(file, out).is_err() {
        println!("Ошибка: Не удалось записать файл {}", file);
    }
}

fn load_db(db: &mut Db, file: &str) {
    let bytes = match fs::read(file) {
        Ok(b) => b,
        Err(_) => return,
    };
    let content = String::from_utf8_lossy(&bytes);

    for line in content.lines() {
        let mut toks = line.split_ascii_whitespace();
        let ty = match toks.next() {
            Some(t) => t,
            None => continue,
        };
        let name = match toks.next() {
            Some(n) => n,
            None => continue,
        };
        let vals: Vec<&str> = toks.collect();

        match ty {
            "M" => {
                if let Some(a) = get_or_create(&mut db.arrs, &mut db.types, name, 'M') {
                    for v in &vals {
                        a.insert_tail(v);
                    }
                }
            }
            "F" => {
                if let Some(l) = get_or_create(&mut db.uls, &mut db.types, name, 'F') {
                    for v in &vals {
                        l.insert_tail(v);
                    }
                }
            }
            "L" => {
                if let Some(l) = get_or_create(&mut db.dls, &mut db.types, name, 'L') {
                    for v in &vals {
                        l.insert_tail(v);
                    }
                }
            }
            "S" => {
                if let Some(s) = get_or_create(&mut db.sts, &mut db.types, name, 'S') {
                    for v in vals.iter().rev() {
                        s.push(v);
                    }
                }
            }
            "Q" => {
                if let Some(q) = get_or_create(&mut db.qs, &mut db.types, name, 'Q') {
                    for v in &vals {
                        q.push(v);
                    }
                }
            }
            _ => println!("Ошибка: Неизвестный тип структуры в файле: {}", ty),
        }
    }
}

fn print_any(db: &Db, name: &str) {
    match db.types.get(name) {
        None => println!("Ошибка: Контейнер {} не найден", name),
        Some(&'M') => db.arrs[name].print(),
        Some(&'F') => db.uls[name].print_iter(),
        Some(&'L') => db.dls[name].print_iter(),
        Some(&'S') => db.sts[name].print(),
        Some(&'Q') => db.qs[name].print(),
        Some(_) => {}
    }
}

#[derive(Clone, Copy)]
enum Cmd {
    Print,
    MCreate, MPush, MInsert, MGet, MDel, MSet, MLen,
    FCreate, FPushHead, FPushTail, FPushBefore, FPushAfter,
    FDelHead, FDelTail, FDelBefore, FDelAfter, FDel, FGet, FPrintRec,
    LCreate, LPushHead, LPushTail, LPushBefore, LPushAfter,
    LDelHead, LDelTail, LDelBefore, LDelAfter, LDel, LGet, LPrintRec,
    SCreate, SPush, SPop,
    QCreate, QPush, QPop,
}

struct CmdInfo {
    cmd: Cmd,
    argc: usize,
    changes: bool,
}

fn find_cmd(name: &str) -> Option<CmdInfo> {
    let (cmd, argc, changes) = match name {
        "PRINT" => (Cmd::Print, 2, false),

        "MCREATE" => (Cmd::MCreate, 2, true),
        "MPUSH" => (Cmd::MPush, 3, true),
        "MINSERT" => (Cmd::MInsert, 4, true),
        "MGET" => (Cmd::MGet, 3, false),
        "MDEL" => (Cmd::MDel, 3, true),
        "MSET" => (Cmd::MSet, 4, true),
        "MLEN" => (Cmd::MLen, 2, false),

        "FCREATE" => (Cmd::FCreate, 2, true),
        "FPUSHHEAD" => (Cmd::FPushHead, 3, true),
        "FPUSHTAIL" => (Cmd::FPushTail, 3, true),
        "FPUSHBEFORE" => (Cmd::FPushBefore, 4, true),
        "FPUSHAFTER" => (Cmd::FPushAfter, 4, true),
        "FDELHEAD" => (Cmd::FDelHead, 2, true),
        "FDELTAIL" => (Cmd::FDelTail, 2, true),
        "FDELBEFORE" => (Cmd::FDelBefore, 3, true),
        "FDELAFTER" => (Cmd::FDelAfter, 3, true),
        "FDEL" => (Cmd::FDel, 3, true),
        "FGET" => (Cmd::FGet, 3, false),
        "FPRINTREC" => (Cmd::FPrintRec, 2, false),

        "LCREATE" => (Cmd::LCreate, 2, true),
        "LPUSHHEAD" => (Cmd::LPushHead, 3, true),
        "LPUSHTAIL" => (Cmd::LPushTail, 3, true),
        "LPUSHBEFORE" => (Cmd::LPushBefore, 4, true),
        "LPUSHAFTER" => (Cmd::LPushAfter, 4, true),
        "LDELHEAD" => (Cmd::LDelHead, 2, true),
        "LDELTAIL" => (Cmd::LDelTail, 2, true),
        "LDELBEFORE" => (Cmd::LDelBefore, 3, true),
        "LDELAFTER" => (Cmd::LDelAfter, 3, true),
        "LDEL" => (Cmd::LDel, 3, true),
        "LGET" => (Cmd::LGet, 3, false),
        "LPRINTREC" => (Cmd::LPrintRec, 2, false),

        "SCREATE" => (Cmd::SCreate, 2, true),
        "SPUSH" => (Cmd::SPush, 3, true),
        "SPOP" => (Cmd::SPop, 2, true),

        "QCREATE" => (Cmd::QCreate, 2, true),
        "QPUSH" => (Cmd::QPush, 3, true),
        "QPOP" => (Cmd::QPop, 2, true),

        _ => return None,
    };
    Some(CmdInfo { cmd, argc, changes })
}

fn run(db: &mut Db, cmd: Cmd, t: &[String]) {
    match cmd {
        Cmd::Print => print_any(db, &t[1]),

        Cmd::MCreate => {
            get_or_create(&mut db.arrs, &mut db.types, &t[1], 'M');
        }
        Cmd::MPush => {
            if let Some(a) = get_or_create(&mut db.arrs, &mut db.types, &t[1], 'M') {
                a.insert_tail(&t[2]);
            }
        }
        Cmd::MInsert => {
            if let Some(a) = find_cont(&mut db.arrs, &t[1]) {
                if let Some(idx) = to_int(&t[2]) {
                    a.insert_idx(&t[3], idx);
                }
            }
        }
        Cmd::MGet => {
            if let Some(a) = find_cont(&mut db.arrs, &t[1]) {
                if let Some(idx) = to_int(&t[2]) {
                    let v = a.search(idx);
                    if idx >= 0 && idx < a.size() {
                        println!("{}", v);
                    }
                }
            }
        }
        Cmd::MDel => {
            if let Some(a) = find_cont(&mut db.arrs, &t[1]) {
                if let Some(idx) = to_int(&t[2]) {
                    a.delete_idx(idx);
                }
            }
        }
        Cmd::MSet => {
            if let Some(a) = find_cont(&mut db.arrs, &t[1]) {
                if let Some(idx) = to_int(&t[2]) {
                    a.change_idx(&t[3], idx);
                }
            }
        }
        Cmd::MLen => {
            if let Some(a) = find_cont(&mut db.arrs, &t[1]) {
                println!("{}", a.size());
            }
        }

        Cmd::FCreate => {
            get_or_create(&mut db.uls, &mut db.types, &t[1], 'F');
        }
        Cmd::FPushHead => {
            if let Some(l) = get_or_create(&mut db.uls, &mut db.types, &t[1], 'F') {
                l.insert_head(&t[2]);
            }
        }
        Cmd::FPushTail => {
            if let Some(l) = get_or_create(&mut db.uls, &mut db.types, &t[1], 'F') {
                l.insert_tail(&t[2]);
            }
        }
        Cmd::FPushBefore => {
            if let Some(l) = find_cont(&mut db.uls, &t[1]) {
                l.insert_before(&t[2], &t[3]);
            }
        }
        Cmd::FPushAfter => {
            if let Some(l) = find_cont(&mut db.uls, &t[1]) {
                l.insert_after(&t[2], &t[3]);
            }
        }
        Cmd::FDelHead => {
            if let Some(l) = find_cont(&mut db.uls, &t[1]) {
                l.delete_head();
            }
        }
        Cmd::FDelTail => {
            if let Some(l) = find_cont(&mut db.uls, &t[1]) {
                l.delete_tail();
            }
        }
        Cmd::FDelBefore => {
            if let Some(l) = find_cont(&mut db.uls, &t[1]) {
                l.delete_before(&t[2]);
            }
        }
        Cmd::FDelAfter => {
            if let Some(l) = find_cont(&mut db.uls, &t[1]) {
                l.delete_after(&t[2]);
            }
        }
        Cmd::FDel => {
            if let Some(l) = find_cont(&mut db.uls, &t[1]) {
                l.delete_key(&t[2]);
            }
        }
        Cmd::FGet => {
            if let Some(l) = find_cont(&mut db.uls, &t[1]) {
                l.search(&t[2]);
            }
        }
        Cmd::FPrintRec => {
            if let Some(l) = find_cont(&mut db.uls, &t[1]) {
                l.print_rec();
            }
        }

        Cmd::LCreate => {
            get_or_create(&mut db.dls, &mut db.types, &t[1], 'L');
        }
        Cmd::LPushHead => {
            if let Some(l) = get_or_create(&mut db.dls, &mut db.types, &t[1], 'L') {
                l.insert_head(&t[2]);
            }
        }
        Cmd::LPushTail => {
            if let Some(l) = get_or_create(&mut db.dls, &mut db.types, &t[1], 'L') {
                l.insert_tail(&t[2]);
            }
        }
        Cmd::LPushBefore => {
            if let Some(l) = find_cont(&mut db.dls, &t[1]) {
                l.insert_before(&t[2], &t[3]);
            }
        }
        Cmd::LPushAfter => {
            if let Some(l) = find_cont(&mut db.dls, &t[1]) {
                l.insert_after(&t[2], &t[3]);
            }
        }
        Cmd::LDelHead => {
            if let Some(l) = find_cont(&mut db.dls, &t[1]) {
                l.delete_head();
            }
        }
        Cmd::LDelTail => {
            if let Some(l) = find_cont(&mut db.dls, &t[1]) {
                l.delete_tail();
            }
        }
        Cmd::LDelBefore => {
            if let Some(l) = find_cont(&mut db.dls, &t[1]) {
                l.delete_before(&t[2]);
            }
        }
        Cmd::LDelAfter => {
            if let Some(l) = find_cont(&mut db.dls, &t[1]) {
                l.delete_after(&t[2]);
            }
        }
        Cmd::LDel => {
            if let Some(l) = find_cont(&mut db.dls, &t[1]) {
                l.delete_key(&t[2]);
            }
        }
        Cmd::LGet => {
            if let Some(l) = find_cont(&mut db.dls, &t[1]) {
                l.search(&t[2]);
            }
        }
        Cmd::LPrintRec => {
            if let Some(l) = find_cont(&mut db.dls, &t[1]) {
                l.print_rec();
            }
        }

        Cmd::SCreate => {
            get_or_create(&mut db.sts, &mut db.types, &t[1], 'S');
        }
        Cmd::SPush => {
            if let Some(s) = get_or_create(&mut db.sts, &mut db.types, &t[1], 'S') {
                s.push(&t[2]);
                println!("{}", t[2]);
            }
        }
        Cmd::SPop => {
            if let Some(s) = find_cont(&mut db.sts, &t[1]) {
                s.pop();
            }
        }

        Cmd::QCreate => {
            get_or_create(&mut db.qs, &mut db.types, &t[1], 'Q');
        }
        Cmd::QPush => {
            if let Some(q) = get_or_create(&mut db.qs, &mut db.types, &t[1], 'Q') {
                q.push(&t[2]);
                println!("{}", t[2]);
            }
        }
        Cmd::QPop => {
            if let Some(q) = find_cont(&mut db.qs, &t[1]) {
                q.pop();
            }
        }
    }
}

fn main() {
    let args: Vec<String> = std::env::args().collect();

    let mut file = String::new();
    let mut query = String::new();
    let mut i = 1;
    while i < args.len() {
        if args[i] == "--file" && i + 1 < args.len() {
            i += 1;
            file = args[i].clone();
        } else if args[i] == "--query" && i + 1 < args.len() {
            i += 1;
            query = args[i].clone();
        }
        i += 1;
    }
    if file.is_empty() || query.is_empty() {
        println!("Использование: ./dbms --file file.data --query 'КОМАНДА имя [аргументы]'");
        std::process::exit(1);
    }

    let mut t: Vec<String> = query.split_ascii_whitespace().map(String::from).collect();
    if t.is_empty() {
        println!("Ошибка: Пустой запрос");
        std::process::exit(1);
    }

    t[0] = t[0].to_ascii_uppercase();

    let info = match find_cmd(&t[0]) {
        Some(info) => info,
        None => {
            println!("Ошибка: Неизвестная команда {}", t[0]);
            std::process::exit(1);
        }
    };
    if t.len() != info.argc {
        println!("Ошибка: Неверное число аргументов для {}", t[0]);
        std::process::exit(1);
    }

    let mut db = Db::default();
    load_db(&mut db, &file);
    run(&mut db, info.cmd, &t);

    if info.changes {
        save_db(&db, &file);
    }
}
