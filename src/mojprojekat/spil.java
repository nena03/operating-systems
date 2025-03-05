package mojprojekat;
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

public class spil 
{
    private final List<karta> kartice = new ArrayList<>();
    private static final int broj = 52;
    public void dodajkarteuspil() 
    {
    
        String[] znakovi = {"srculence", "tref", "karo", "pik"};
        for (String znak : znakovi) 
        {
            for (int i = 1; i <= 13; i++) 
            {
                kartice.add(new karta(i, znak));
            }
        }
        Collections.shuffle(kartice);
    }

    public synchronized karta Getcard() throws InterruptedException 
    {
        while (kartice.isEmpty()) 
        {
            wait(); 
        }
        karta karta1 = kartice.remove(kartice.size() - 1);
        notifyAll();
        return karta1;
    }
    public spil() {}

    public synchronized void dodaj(karta karta1) throws InterruptedException 
    {
        while (kartice.size() >= broj) 
        {
            wait();
        }
        kartice.add(karta1);
        notifyAll();
    }

    @Override
    public String toString() {
        return "karte u ovom spilu su: " + kartice.toString();
    }
}

