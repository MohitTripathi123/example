# example
Implement a Hash Table
Please implement a hash table data storage. The data should be stored using string keys and
needs to store string values. Libraries or platform support for hash tables (or similar structures)
cannot be used.
Please ensure that your implementation addresses the following points. Please provide code
comments, and also be able to demonstrate and explain these points as well:
 O(1) run time for value look up
 Suitability of the chosen hash function
 Resizing of the hash table when adding/removing key-value pairs to/from the hash table

Shared Queue
Please implement a shared queue that is intended to be accessed by multiple readers and a single
writer. The queue receives and releases string objects. Provide a test program that showcases the
use of the queue; the sample program shall create 5 threads that consume the strings from the
queue, and a single writer that adds the strings to the queue. The writer should add 5 messages a
second, and the messages should be distributed relatively evenly between the consumers.
Note: consumers or the queue functionality that facilitates the message consumption should not
use Thread.sleep(), SLEEP(3) or similar calls, and the message consumption process should
not spin on the CPU.
Libraries or platform support for queues (or similar structures) should not be used.
Please ensure that your implementation addresses the following points. Please provide code
comments, and also be able to demonstrate and explain these points as well:
 How is synchronization between the readers and the writer implemented
 Whether multiple readers can wait for the next message without blocking each other
access
 If synchronization is used, how the time spent in a locked condition is minimized
Implement Client-Server Data Exchange
Implement a server and a client. The server shall support responding to a single “ping” message
with a “pong” response. The request-response data can be strings, or simple tokens. The protocol
used can be either Layer 4 (e.g., TCP), or Layer 7 (e.g., HTTP), but must be connection oriented.
The client, once started, must connect to the server only once, and start sending “ping” message,
printing the fact that the message is sent, and reporting when a “pong” response is received.
Clients shall continue sending “ping” messages each second (whether responses are received or
not). The server must support multiple clients simultaneously.
If the server encountered an error, it should display an error and continue working. If the client
encounters an error, it should display an error and stop.
The client shall take in program parameter indicating where to connect, and the server shall take
in a program parameter specifying how to listen to incoming client connections.
High level server frameworks shall not be used (i.e., no J2EE, Spring, Express, etc.)
Please ensure that your implementation addresses the following points. Please provide code
comments, and also be able to demonstrate and explain these points as well:
 How does the server handle multiple clients simultaneously
 Suitability of your choice of protocol for the task
 Network error handling on both the client and the server
