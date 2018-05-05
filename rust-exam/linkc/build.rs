extern crate gcc;

fn main(){
    gcc::Config::new()
        .file("src/c/hello.c")
        .include("src")
        .compile("libhello.a");
}
