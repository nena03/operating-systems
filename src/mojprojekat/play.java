package mojprojekat;
import mojprojekat.ucesnik;
import mojprojekat.spil;
import mojprojekat.karta;
import mojprojekat.partija;
public class play 
{
    public static void main(String[] args) throws InterruptedException 
    {
        System.out.println("pocetak igre, spremite se!");
        spil spil1 = new spil();
        spil1.dodajkarteuspil();
	ucesnik Jana = new ucesnik("Jana");
        ucesnik Majda = new ucesnik("Majda");

        partija igra = new partija(spil1, new ucesnik[]{Jana, Majda});

        for (int i = 0; i < 3; i++) 
        {
            Jana.Getcard(spil1);
            Majda.Getcard(spil1);  
        }

        for (int i = 0; i < 5; i++) 
        {
            igra.Partija();
        }

        
        System.out.println(spil1);
        System.out.println(Jana);
        System.out.println(Majda);

        ucesnik winer = igra.Winer();
        System.out.println("Pobednik je " + winer.ime + " njegov zbir je " + winer.zbirkarata());
    }
}

