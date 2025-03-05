package mojprojekat;

public class karta 
{
    private final int value;
    private final String znak; 
    private static int brojac = 0;
    private final int id;
   
    public karta(int value, String znak) 
    {
        this.value = value;
        this.znak = znak;
        this.id = ++brojac;
    }
    public String dajznak() 
    {
     
        return znak;
    }

    public karta kopiraj() 
    {
        return new karta(this.value, this.znak);
    }


    public int dajvalue() 
    {
        return value;
    }

   
    @Override
    public String toString() {
        return value + " " + znak;
    }
}

