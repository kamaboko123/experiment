#include <cstdio>

namespace easy_stack{
    class error{};
    
    template <typename T>
    class stack{
    private:
        T *_bottom;
        T *_sp;
        std::uint16_t _max_size;
        std::uint16_t _size;
        
        stack<T>(const stack<T> &src){};
        stack<T> &operator=(const stack<T> &src){};
        
    public:
        stack<T>(std::uint16_t stack_size){
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
        
        void sp(uint16_t p){
            _sp = _bottom + p;
            _size = p;
        }
        
        T* bottom(){
            return(_bottom);
        };
        
        T offset(){
            return(_sp - _bottom);
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
