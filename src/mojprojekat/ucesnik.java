package mojprojekat;
import java.util.ArrayList;
import java.util.List;

public class ucesnik 
{
    public final String ime;
    public final List<karta> ucesnikovekarte = new ArrayList<>();

    public ucesnik(String ime) 
    {
        this.ime = ime;
    }
    public ucesnik(String ime, List<karta> njegovekarte) {
        this.ime = ime;
        this.ucesnikovekarte.addAll(njegovekarte);
    }

    public int zbirkarata() 
    {
        return ucesnikovekarte.stream().mapToInt(karta::dajvalue).sum();//pomocu Stream racunamo sumu vred
    }

    @Override
    public String toString() {
        return ime + ": " + ucesnikovekarte.toString();
    }
    
    public synchronized void Getcard(spil spil1) throws InterruptedException 
    {
        ucesnikovekarte.add(spil1.Getcard());
    }

    public synchronized void Play(spil spil1, int id) throws InterruptedException {
        if (id >= 0 && id < ucesnikovekarte.size()) {
            spil1.dodaj(ucesnikovekarte.remove(id));
        }
    }
}
