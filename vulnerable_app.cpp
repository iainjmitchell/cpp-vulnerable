#include <iostream>
#include <cstring>
#include <vector>
#include <cstdlib> // Needed for system()

// CWE-78: OS Command Injection
void execute_ping(const char* ip_address) {
    char command[128];
    // BAD: Directly concatenating user input into a system command
    // An attacker could pass: "8.8.8.8 ; rm -rf /"
    sprintf(command, "ping -c 1 %s", ip_address);
    
    std::cout << "Executing command: " << command << std::endl;
    system(command); 
}

// CWE-121: Stack-based Buffer Overflow
void stack_overflow(const char* input) {
    char buffer[16];
    strcpy(buffer, input); 
    std::cout << "Buffer content: " << buffer << std::endl;
}

// CWE-416: Use After Free
void use_after_free() {
    int* data = new int(100);
    delete data; 
    std::cout << "Stale data value: " << *data << std::endl; 
}

// Adding to see how the insertion of the stack trace affects the finding identity
void print_stack_trace() {
    void* array[10];
    size_t size;
    char** strings;
    size = backtrace(array, 10);
    strings = backtrace_symbols(array, size);
    for (size_t i = 0; i < size; i++) {
        std::cout << strings[i] << std::endl;
    }
    free(strings);
}

// CWE-476: NULL Pointer Dereference - Null value carrier
void null_deref(int* ptr) {
    if (*ptr > 0) { 
        std::cout << "Value is positive" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        // Test Command Injection: ./vulnerable_app "8.8.8.8; ls"
        execute_ping(argv[1]);
        
        // Test Buffer Overflow
        stack_overflow(argv[1]);
    }
    
    use_after_free();
    null_deref(nullptr);
    
    return 0;
}