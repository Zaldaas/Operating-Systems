## PROJECT OUTCOMES
1. Implement applications using fork(), exec(), and wait() system calls.
2. Design and implement multi-process applications.
3. Describe fault-tolerance benefits of multi-process applications.
4. Empirically evaluate the performance of serial vs parallel applications.
5. Implement basic process management functions within applications.
6. Explain how the permission inheritance works between parent and child processes.

## GROUP MEMBERS
Zeid Aldaas - zaldaas@csu.fullerton.edu

## CONTRIBUTIONS
I did the whole project.

## FAMILIARITY
I am familiar with all of the functionality in the assignment.

## LANGUAGE
C++

## HOW TO EXECUTE
Once you have the zip extracted, you should be able to type the following to run all 4 files created for the project to get all the information necessary:
`g++ -o serial serial.cpp`
`g++ -o parallel parallel.cpp`
`g++ multi-search.cpp -o multi-search`
`g++ shell.cpp -o shell`
`time ./serial`
`time ./parallel`
`./multi-search <FILE NAME> <KEY> <NUMBER OF PROCESSES>`
`./shell`

## EXECUTION TIMES
Serial:
- real	0m1.965s
- user	0m0.112s
- sys	0m0.072s

Parallel:
- real	0m0.364s
- user	0m0.139s
- sys	0m0.093s

## QUESTION ANSWERS
Q: In the output of time, what is the difference between real, user, and sys times?
A: Real: This is the actual elapsed time (also known as wall-clock time). It's the time difference between when you started the command and when the command finished.

User: This is the amount of CPU time spent in user mode. This means the time the CPU spent running your code (non-kernel code).

Sys: This is the amount of CPU time spent in kernel mode (system calls, handling I/O etc.)

Q: Which is longer: user time or sys time? Use your knowledge to explain why.
A: In most programs, user time is typically longer than sys time because the majority of the time is spent executing program code rather than executing system calls in the kernel.

Q: When fetching all of the locations in the file, which fetcher finishes faster? Why do you think that is?
A: The parallel fetcher will generally finish faster as it's fetching data for all the locations simultaneously. The serial fetcher fetches data one at a time, waiting for each request to complete before starting the next.

Q: Suppose one of the fetcher children crashes. Will this affect other children? Explain. What is your conclusion regarding the benefits or disadvantages of isolating each fetch task within a different process?
A: If one child process crashes, it won't directly affect other child processes. Each child process runs in its own address space due to isolation, so a failure in one won't directly impact the others. However, the parent process needs to handle the crashed child appropriately, using mechanisms like wait() or waitpid(), to ensure it doesn't leave behind any "zombie" processes. 
Thus, the advantage of isolating each fetch in a different process is this resilience against crashes, while the downside is the overhead of creating and managing these processes, which is higher than threads.

## EXTRA CREDIT?
Yes, I implemented the extra credit.

## ANYTHING SPECIAL?
No.
