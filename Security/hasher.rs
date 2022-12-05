use std::collections::HashMap;
use std::hash::{Hash, Hasher};
use std::sync::{Arc, Mutex};

struct HasherWrapper(Arc<Mutex<Hasher>>);

impl Hasher for HasherWrapper {
    fn finish(&self) -> u64 {
        self.0.lock().unwrap().finish()
    }

    fn write(&mut self, bytes: &[u8]) {
        self.0.lock().unwrap().write(bytes);
    }
}

fn hash_password(password: &str) -> u64 {
    let hasher = std::collections::hash_map::DefaultHasher::new();
    let hasher = HasherWrapper(Arc::new(Mutex::new(hasher)));
    password.hash(&hasher);
    hasher.finish()
}

fn main() {
    let mut users: HashMap<u64, String> = HashMap::new();

    users.insert(hash_password("secret"), "johndoe".to_string());
    users.insert(hash_password("password"), "janedoe".to_string());

    println!("Utilisateurs : {:?}", users);
}
