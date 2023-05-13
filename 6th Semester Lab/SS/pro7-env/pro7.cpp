#include <iostream>

struct proc
{
  int id;
  int arrival;
  int burst;
  int rem;
  int wait;
  int finish;
  int turnaround;
  float ratio;
}process[10];
struct proc temp;
int no;
int chkprocess(int);
int nextprocess();
void roundrobin(int, int, int[], int[]);
void srtf(int);

int main()
{
  int n, tq, choice;
  int bt[10], st[10], i, j, k;
  for (;;)
  {
    std::cout << "Enter the choice in C++\n";
    std::cout << " 1. Round Robin\n 2. SRT\n 3. Exit \n";
    std::cin >> choice;
    switch (choice)
    {
    case 1:
      std::cout << "Round Robin scheduling algorithm\n";
      std::cout << "Enter number of processes:\n";
      std::cin >> n;
      std::cout << "Enter burst time for sequences:\n";
      for (i = 0; i < n; i++)
      {
        std::cin >> bt[i];
        st[i] = bt[i];
      }
      std::cout << "Enter time quantum:\n";
      std::cin >> tq;
      roundrobin(n, tq, st, bt);
      break;

    case 2:
      std::cout << "\n \n ---SHORTEST REMAINING TIME NEXT---\n \n ";
      std::cout << "\n \n Enter the number of processes: ";
      std::cin >> n;
      srtf(n);
      break;
    case 3:
      exit(0);
    }
  }
}

void roundrobin(int n, int tq, int st[], int bt[])
{
  int time = 0;
  int tat[10], wt[10], i, count = 0, swt = 0, stat = 0, temp1, sq = 0, j, k;
  float awt = 0.0, atat = 0.0;
  while (1)
  {
    for (i = 0, count = 0; i < n; i++)
    {
      temp1 = tq;
      if (st[i] == 0)
      {
        count++;
        continue;
      }
      if (st[i] > tq)
      {
        st[i] = st[i] - tq;
      }
      else if (st[i] >= 0)
      {
        temp1 = st[i];
        st[i] = 0;
      }
      sq = sq + temp1;
      tat[i] = sq;
    }
    if (n == count)
      break;
  }
  for (i = 0; i < n; i++)
  {
    wt[i] = tat[i] - bt[i];
    swt = swt + wt[i];
    stat = stat + tat[i];
  }
  awt = (float)swt / n;
  atat = (float)stat / n;
  std::cout << "Process_no Burst time Wait time Turn around time\n";
  for (i = 0; i < n; i++)
    std::cout << i + 1 << "\t\t" << bt[i] << "\t\t" << wt[i] << "\t\t" << tat[i] << "\n";
  std::cout << "Avg wait time is " << awt << "\n Avg turn around time is " << atat << "\n";
}

int chkprocess(int s)
{
  int i;
  for (i = 1; i <= s; i++)
  {
    if (process[i].rem != 0)
      return 1;
  }
  return 0;
}

////////////////////////


int nextProcess() {
  int min, l, i;
  min = 32000;
  for (i = 1; i <= no; i++) {
    if (process[i].rem != 0 && process[i].rem < min) {
      min = process[i].rem;
      l = i;
    }
  }
  return l;
}

void srtf(int n) {
  int i, j, k, time = 0;
  float tavg, wavg;
  for (i = 1; i <= n; i++) {
    process[i].id = i;
    cout << "\n\nEnter the arrival time for process " << i << ": ";
    cin >> process[i].arrival;
    cout << "Enter the burst time for process " << i << ": ";
    cin >> process[i].burst;
    process[i].rem = process[i].burst;
  }
  for (i = 1; i <= n; i++) {
    for (j = i + 1; j <= n; j++) {
      if (process[i].arrival > process[j].arrival) {
        Process temp = process[i];
        process[i] = process[j];
        process[j] = temp;
      }
    }
  }
  no = 0;
  j = 1;
  while (chkprocess(n) == 1) {
    if (process[no + 1].arrival == time) {
      while (process[no + 1].arrival == time) {
        no++;
      }
      if (process[j].rem == 0) {
        process[j].finish = time;
      }
      j = nextProcess();
    }
    if (process[j].rem != 0) {
      process[j].rem--;
      for (i = 1; i <= no; i++) {
        if (i != j && process[i].rem != 0) {
          process[i].wait++;
        }
      }
    } else {
      process[j].finish = time;
      j = nextProcess();
      time--;
      k = j;
    }
    time++;
  }
  process[k].finish = time;
  cout << "\n\n\t\t\t---SHORTEST REMAINING TIME FIRST---\n\n";
  cout << "\n\n Process Arrival Burst Waiting Finishing turnaround Tr/Tb \n";
  cout << "%5s %9s %7s %10s %8s %9s\n\n", "id", "time", "time", "time", "time", "time";
  for (i = 1; i <= n; i++) {
    process[i].turnaround = process[i].wait + process[i].burst;
    process[i].ratio = (float)process[i].turnaround / (float)process[i].burst;
    cout << "%5d %8d %7d %8d %10d %9d %10.1f ", process[i].id, process[i].arrival, process[i].burst,
      process[i].wait, process[i].finish, process[i].turnaround, process[i].ratio;
    tavg += process[i].turnaround;
    wavg += process[i].wait;
    cout << "\n\n";
  }
  tavg /= n;
  wavg /= n;
  cout << "tavg=" << tavg << "\t wavg=" << wavg << endl;
}





