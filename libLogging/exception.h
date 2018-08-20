#ifndef _HSLIB_EXCEPTION_H_INCLUDED_
#define _HSLIB_EXCEPTION_H_INCLUDED_

#include <string>

namespace hslib {

    //! General purpose exception
    /**
     * General purpose exception class.
     */
    class Exception
    {
        private:
            /** Exception message */
            std::string message;
        public:
            /**
             * Default constructor.
             */
            Exception() : message() { }
            /**
             * Copy constructor.
             * \param copy Exception object to copy.
             */
            Exception(const Exception& copy) : message(copy.message) { }
            /**
             * Parameter constructor that takes a message as its only parameter.
             * \param message Exception message.
             */
            explicit Exception(const std::string& message) : message(message) { }
            /**
             * Assignment operator.
             * \param copy Exception object to copy.
             * \return Reference to this object.
             */
            Exception& operator=(const Exception& copy) { message = copy.message; return *this; }
            /**
             * Return the current exception message.
             * \return Exception message.
             */
            const std::string getMessage() const { return message; }
            /**
             * Set the exception message.
             * \param message New exception message.
             * \return Reference to this object.
             */
            Exception& setMessage(const std::string& message) { this->message = message; return *this; }
    };
} // hslib

#endif // _HSLIB_EXCEPTION_H_INCLUDED_
