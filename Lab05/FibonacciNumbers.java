import java.io.FileWriter;
import java.io.IOException;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.math.MathContext;
import java.util.ArrayList;


public class FibonacciNumbers extends Thread {
    int N;
    int maxThreads;
    int threadIndex;
    BigInteger[] results;

    FibonacciNumbers(int N, int maxThreads, int threadIndex, BigInteger[] results)
    {
        this.N = N;
        this.maxThreads = maxThreads;
        this.threadIndex = threadIndex;
        this.results = results;
    }

    public void run() {
        
        MathContext MC = new MathContext(this.N);
        BigDecimal FIVE = BigDecimal.valueOf(5.0).sqrt(MC);
        BigDecimal TWO = BigDecimal.valueOf(2.0);

        BigDecimal PHI = BigDecimal.ONE.add(FIVE, MC).divide(TWO, MC);

        int initialIndex = this.threadIndex;
        while (initialIndex <= this.N) {
            this.results[initialIndex] = (PHI.pow(initialIndex, MC))
                    .divide((FIVE), MC)
                    .add(BigDecimal.valueOf(0.5), MC).toBigInteger();
            initialIndex += this.maxThreads;
        }
    }

    public static void main(String[] args) throws InterruptedException, IOException {
        long sp = System.currentTimeMillis();
        int N = 8500;

        int maxThreads = 24;
        BigInteger[] results = new BigInteger[N + 1];

        ArrayList<FibonacciNumbers> fibs = new ArrayList<>();

        for (int i = 1; i <= maxThreads; i++)
        {
            FibonacciNumbers t = new FibonacciNumbers(N, maxThreads, i, results);
            fibs.add(t);
        }

        for (Thread f: fibs)
        {
            f.start();
        }

        for (Thread f: fibs)
        {
            f.join();
        }
        System.out.println("spent (ms): " + (System.currentTimeMillis() - sp));

        FileWriter myWriter = new FileWriter("Fibonacci.txt");
        for (int i = 1; i <= N; i++) {
            myWriter.write("F(" + i + "): " + results[i] + "\n");
        }
        myWriter.close();
    }
}
