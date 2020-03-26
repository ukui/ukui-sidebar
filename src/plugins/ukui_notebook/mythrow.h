#ifndef MYTHROW_H
#define MYTHROW_H

#include <exception>
#include <string>

#define MY_THROW(ExClass, args...)                             \
     do                                                         \
     {                                                          \
         ExClass e(args);                                       \
         e.Init(__FILE__, __PRETTY_FUNCTION__, __LINE__);       \
         throw e;                                               \
     }                                                          \
     while (false)

#define MY_DEFINE_EXCEPTION(ExClass, Base)                     \
    ExClass(const std::string& msg = "") throw()               \
        : Base(msg)                                            \
    {}                                                         \
                                                               \
    ~ExClass() throw() {}                                        \
                                                               \
    /* override */ std::string GetClassName() const            \
    {                                                          \
        return #ExClass;                                       \
    }

class ExceptionBase : public std::exception
{
public:
    ExceptionBase(const std::string& msg = "") throw();

    virtual ~ExceptionBase() throw();

    void Init(const char* file, const char* func, int line);

    virtual std::string GetClassName() const;

    virtual std::string GetMessage() const;

    const char* what() const throw();

    const std::string& ToString() const;
    //打印函数栈
    std::string GetStackTrace() const;

protected:
    std::string mMsg;
    const char* mFile;
    const char* mFunc;
    int mLine;

private:
    enum { MAX_STACK_TRACE_SIZE = 50 };//最大调用栈深度
    void* mStackTrace[MAX_STACK_TRACE_SIZE];
    size_t mStackTraceSize;
    mutable std::string mWhat;
};

class ExceptionDerived : public ExceptionBase
{
public:
    MY_DEFINE_EXCEPTION(ExceptionDerived, ExceptionBase);
};

#endif // MYTHROW_H
