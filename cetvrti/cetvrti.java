
import java.util.Random;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;

public class cetvrti implements Callable<Integer> {
    private final int[][] m; // naša matrica
    private final String n; // nit

    public cetvrti(int[][] m, String n) { // konstruktor
        this.m = m;
        this.n = n;
    }

    @Override
    public Integer call() {
        int zbir = 0;
        System.out.println(n + " preuzela zadatak:");
        for (int i = 0; i < m.length; i++) {
            for (int j = 0; j < m[i].length; j++) {
                System.out.print(m[i][j] + " ");
                if (i == j) {
                    zbir += m[i][j];
                }
            }
            System.out.println();
        }
        System.out.println("Konačan zbir po dijagonali: " + zbir);
        return zbir;
    }

    public static void main(String[] args) {
        ExecutorService executorService = Executors.newFixedThreadPool(5);
        BlockingQueue<int[][]> queue = new ArrayBlockingQueue<>(10);
        Random r = new Random();
        AtomicBoolean cekaj = new AtomicBoolean(false);
        AtomicInteger brojac = new AtomicInteger(0);

        //za dodavanje u red
        Thread producer = new Thread(() -> {
            while (!cekaj.get() && brojac.get() < 10) {
                try {
                    int[][] m = new int[10][10];
                    for (int i = 0; i < 10; i++) {
                        for (int j = 0; j < 10; j++) {
                            m[i][j] = r.nextInt(60);
                        }
                    }
                    System.out.println("Napravljena matrica");
                    queue.put(m);
                    brojac.incrementAndGet();
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    e.printStackTrace();
                }
            }
            //da zaustavim proces iteracije
            cekaj.set(true);
        });

        
        producer.start();

        
        while (!cekaj.get() || !queue.isEmpty()) {
            try {
                int[][] m = queue.poll(1, TimeUnit.SECONDS);
                if (m != null) {
                    Future<Integer> rez = executorService.submit(new cetvrti(m, "thread-" + brojac.get()));
                    try {
                        int dijagonalnizbir = rez.get();
                        if (dijagonalnizbir > 300) {
                            cekaj.set(true);
                            System.out.println("Zbir na dijagonali je prešao 300, prekid izvršavanja.");break;
                        }
                    } catch (InterruptedException | ExecutionException e) {
                        e.printStackTrace();
                    }
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        executorService.shutdownNow();
        try {
            if (!executorService.awaitTermination(1, TimeUnit.SECONDS)) {
                System.out.println("Error, imamo neke niti koje još obavljaju svoj zadatak.");
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
