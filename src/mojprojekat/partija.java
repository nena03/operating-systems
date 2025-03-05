package mojprojekat;
import java.util.Random;

public class partija 
{
    private final spil spil1;
    private final ucesnik[] ucesnici;
    private final Random r = new Random();
    public partija(spil spil1, ucesnik[] ucesnici) 
    {
        this.ucesnici = ucesnici;
        this.spil1 = spil1;
    }
    

    public ucesnik Winer() 
    {
        ucesnik winer = ucesnici[0];
        for (ucesnik ucesnik1 : ucesnici) 
        {
            if (ucesnik1.zbirkarata() > winer.zbirkarata()) 
            {
                winer = ucesnik1;
            }
        }
        return winer;
    }
    public void Partija() throws InterruptedException 
    {
        for (ucesnik ucesnik1 : ucesnici) 
        {
            if (r.nextBoolean()) 
            {
                ucesnik1.Getcard(spil1);
            } 
            else 
            {
                if (ucesnik1.zbirkarata() > 0) {
                    int idkarte = r.nextInt(ucesnik1.ucesnikovekarte.size());
                    ucesnik1.Play(spil1, idkarte);
                }
            }
        }
    }
}

