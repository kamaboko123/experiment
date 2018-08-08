#include <cstdio>

namespace easy_stack{
    class error{};
    
    template <typename T>
    class stack{
    private:
        T *_bottom;
        T *_top;
        std::size_t _max_size;
        std::size_t _size;
        
        stack<T>(const stack<T> &src){};
        stack<T> &operator=(const stack<T> &src){};
        
    public:
        stack<T>(std::size_t stack_size){
            _max_size = stack_size;
            _size = 0;
            _bottom = new T[_max_size]();
            _top = _bottom;
        }
        
        ~stack(){
            delete _bottom;
        }
        
        bool push(T data){
            if(_size >= _max_size) return false;
            
            *_top = data;
            _top++;
            _size++;
            return true;
        }
        
        bool pop(){
            if(_size == 0) return false;
            _top--;
            _size--;
            return false;
        }
        
        T top(){
            if(_size <= 0){
                error e;
                throw e;
            }
            return *(_top - 1);
        }
        
        void _dump(){
            T *p = _top - 1;
            fprintf(stderr, "|");
            while(p >= _bottom){
                fprintf(stderr, " 0x%.02x", *p);
                p--;
            }
            fprintf(stderr, " |\n");
        }
    };
}
