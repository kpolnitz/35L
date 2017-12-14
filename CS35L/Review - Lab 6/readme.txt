For the most part, it was easy to infer some of the changes
that had to be made based off of the earlier syntax 
of the main.c code.
 
Some of the problems I ran into involved variable errors,
in using vi and also having to create functions, you need
to make sure that everything is accessible.
With this idea, I also had problems running my code from
cutting/replacing parts of the main function. Some 
problems that I thought were extremely problematic were 
fixed by elementary methods of tracing over the code
carefully.

Another problem I ran into was the issue of the precision
of the last coordinate of the output. I would consistently
get the right coordinates, but my 255 (for example) would
display as 255.000000, which of course was a problem for
creating the diff files. I realized that it happened as
a result of a while loop I had, in addition to there
being a typo in my print command. 

This also resolved another error I had: I would
consistently get a make error for check. I do believe
that this was because the diff file was really far off
and misaligned.

Sometimes, it was also hard to pinpoint specific issues if 
my program just caused errors in make clean check.
It was especially hard trying to figure out this problem
because it was not an easy task to try to build an executable
that caters to all of the special tags that main.c needed
(lm, gammas, etc.). I ultimately looked to the gcc commands
of the Makefile and sometimes implemented them separately
on their own to find specific lines of codes that were 
problematic.

In regards to the implementation of the pthread commands,
they were covered thoroughly in class with adequate examples
that made it easy to mimic in creating the main.c file.

My conclusion that I arrived at is that multithreading is 
an efficient alternative that can minimize time-wasted
in running a program. We can see that with some of the
time output we got:

time ./srt 1-test.ppm >1-test.ppm.tmp

real	0m45.188s
user	0m45.182s
sys	0m0.001s

time ./srt 2-test.ppm >2-test.ppm.tmp

real	0m22.731s
user	0m45.030s
sys	0m0.009s

time ./srt 4-test.ppm >4-test.ppm.tmp

real	0m11.266s
user	0m44.735s
sys	0m0.002s

time ./srt 8-test.ppm >8-test.ppm.tmp

real	0m5.774s
user	0m44.812s
sys	0m0.004s

With 8 threads, we were able to cut the performance time by almost 7/8 
of our time with 1 thread (in real execution time). 
Faster processing allows for other processes to start after. 
Overall, we can see that threads could
improve the overall efficiency of a program.
