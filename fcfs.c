#include<stdio.h>

int main() {
int n, bt[20], wt[20], tat[20], at[20], ct[20];
int i;
float twt = 0.0, ttat = 0.0, awt, att;

printf(&quot;Enter the number of processes: &quot;);
scanf(&quot;%d&quot;, &amp;n);

for (i = 0; i &lt; n; i++) {
printf(&quot;Enter Arrival Time for Process %d: &quot;, i + 1);
scanf(&quot;%d&quot;, &amp;at[i]);
printf(&quot;Enter Burst Time for Process %d: &quot;, i + 1);
scanf(&quot;%d&quot;, &amp;bt[i]);
}

ct[0] = at[0] + bt[0];
wt[0] = 0;
tat[0] = bt[0];

for (i = 1; i &lt; n; i++) {
if (ct[i - 1] &lt; at[i]) {
ct[i] = at[i] + bt[i];
wt[i] = 0;
} else {
wt[i] = ct[i - 1] - at[i];
ct[i] = ct[i - 1] + bt[i];
}
tat[i] = wt[i] + bt[i];

}


for (i = 0; i &lt; n; i++) {
twt += wt[i];
ttat += tat[i];
}

awt = twt / n;
att = ttat / n;


printf(&quot;\nPROCESS\tAT\tBT\tCT\tWT\tTAT&quot;);
for (i = 0; i &lt; n; i++) {
printf(&quot;\nP%d\t%d\t%d\t%d\t%d\t%d&quot;,
i + 1, at[i], bt[i], ct[i], wt[i], tat[i]);
}

printf(&quot;\n\nAverage Waiting Time = %.2f&quot;, awt);
printf(&quot;\nAverage Turnaround Time = %.2f\n&quot;, att);

return 0;
}
