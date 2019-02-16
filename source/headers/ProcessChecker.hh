#ifndef PROCESSCHECKER
#define PROCESSCHECKER

#include <iostream> // remove this include
#include <Windows.h>    // Windows API functionality.
#include <TlHelp32.h>   // Additional Windows API functionality.
#include <thread>       // Multi-threading support.
#include <cstdint>      // Alternative integer definitions.

#include "IConditionChecker.hh"     // IConditionChecker interface / superclass.

/**
 * This is an implementation of the IConditionChecker interface. This implementation focuses
 * on checking for a running process. The override for the check_ pure virtual method is
 * designed to use the TlHelp32.h header to snapshot all running processes, and enable the
 * mouseLocker_ instance main thread, if the target process image name is found. The target
 * image name can be specified through the image_name variable in the class.
 */

class ProcessChecker : public IConditionChecker {
protected:
    void check_() override;         // The overriden pure virtual method.

public:
    bool thread_enabled;            // Bool that when true, enables the functionality of the check_ method. When false, check_ keeps running in a loop, but does nothing.
    bool thread_terminate;          // Bool that when true, stops the loop in the check_ method, allowing check_ to return.

    struct Settings : ISettings {
        const char* imageName;      // The image name that will be searched for.
        uint16_t polling_rate;      // How frequently to check for the process (in milliseconds)
        bool play_sound;            // Whether or not a sound should be played when the process is found / not found.
    } settings;

    void kill();    // Method that sets thread_enabled to false, and thread_terminate to true, and joins the check_thread_ in the superclass.

    ProcessChecker(const char*);
    ~ProcessChecker() override;
};

#endif