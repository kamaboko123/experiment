#include <cstdio>

namespace easy_stack{
    class error{};
    
    template <typename T>
    class stack{
    private:
        T *_bottom;
        T *_sp;
        std::size_t _max_size;
        std::size_t _size;
        
        stack<T>(const stack<T> &src){};
        stack<T> &operator=(const stack<T> &src){};
        
    public:
        stack<T>(std::size_t stack_size){
            _max_size = stack_size;
            _size = 0;
            _bottom = new T[_max_size]();
            _sp = _bottom;
        }
        
        ~stack(){
            delete _bottom;
        }
        
        bool push(T data){
            if(_size >= _max_size) return false;
            
            *_sp = data;
            _sp++;
            _size++;
            return true;
        }
        
        bool pop(){
            if(_size == 0) return false;
            _sp--;
            _size--;
            return false;
        }
        
        T top(){
            if(_size <= 0){
                error e;
                throw e;
            }
            return *(_sp - 1);
        }
        
        T *sp(){
            return(_sp);
        }
        
        void _dump(){
            T *p = _sp - 1;
            fprintf(stderr, "|");
            while(p >= _bottom){
                fprintf(stderr, " 0x%.02X", *p);
                p--;
            }
            fprintf(stderr, " |\n");
        }
    };
}
