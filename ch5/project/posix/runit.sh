make fcfs; ./fcfs schedule.txt > output.txt
make sjf; ./sjf schedule.txt >> output.txt
make rr; ./rr schedule.txt >> output.txt
make priority; ./priority schedule.txt >> output.txt
make priority_rr; ./priority_rr schedule.txt >> output.txt
rm *.o fcfs sjf rr priority priority_rr