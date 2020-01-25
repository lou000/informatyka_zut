package lab_7;

import java.io.*;
import java.util.*;
import java.util.zip.*;

public class lab7_Model
{
    public enum CompressionMode
    {
        UNDEFINED,
        GZIP,
        ZIP;
    }
    public enum BackupJob
    {
        UNDEFINED,
        IMPORT,
        EXPORT;
    }
    HashMap<Long, Object> data = new HashMap<Long, Object>();
    public boolean validateKey(long key)
    {
        if((int) (Math.log10(key) + 1)!=11)
            return false;
        int[] weights = {1, 3, 7, 9, 1, 3, 7, 9, 1, 3};
        long temp = key;
        int[] digits = new int[11];
        int sum = 0;

        for(int i=10; i>=0; i--) {
            digits[i] = (int)(long)(temp % 10);
            temp = temp/10;
        }
        for(int i=0; i<weights.length; i++)
        {
            sum+=weights[i]*digits[i];
        }
        sum = 10 - (sum % 10);
        return sum == digits[10];
    }

    public void addWorker(long key, Object worker)
    {
        if(!validateKey(key))
        {
            System.out.println("Nieprawidłowy numer pesel.");
            return;
        }
        if(data.containsKey(key))
            System.out.println("Pracownik o podanym numerze pesel już istnieje");
        else
            data.put(key, worker);
    }
    public Object getWorker(long key)
    {
        return data.get(key);
    }
    public void removeWorker(long key)
    {
        data.remove(key);
    }
    public void exportBackup(String filename, CompressionMode mode)
    {

        try {
        File myFile = new File(filename);
        FileOutputStream fileOutputStream = new FileOutputStream(myFile);
        final ObjectOutputStream objectStream;
        if(mode == CompressionMode.GZIP)
        {
            GZIPOutputStream zipStream = new GZIPOutputStream(fileOutputStream);
            objectStream = new ObjectOutputStream(zipStream);
            data.forEach((key, object) -> {
                try
                {
                    objectStream.writeObject(object);
                    objectStream.flush();
                } catch (IOException e)
                {
                    e.printStackTrace();
                }
            });
            objectStream.close();
            zipStream.close();
            fileOutputStream.close();
        }
        else if(mode == CompressionMode.ZIP)
        {
            ZipOutputStream zipStream = new ZipOutputStream(fileOutputStream);
            ZipEntry entry = new ZipEntry("x");
            zipStream.putNextEntry(entry);
            objectStream = new ObjectOutputStream(zipStream);
            data.forEach((key, object) -> {
                try
                {
                    objectStream.writeObject(object);
                    objectStream.flush();
                } catch (IOException e)
                {
                    e.printStackTrace();
                }
            });
            objectStream.close();
            zipStream.close();
            fileOutputStream.close();
        }
        else return;
        System.out.printf("Plik zapisany do %s\n", myFile.getAbsolutePath());
        } catch(IOException ioe) {
            ioe.printStackTrace();
        }
    }
    public void importBackup(String filename)
    {
        try {
        FileInputStream fileStream = new FileInputStream(filename);
        if(filename.split("\\.")[1].equals("gzip"))
        {
            GZIPInputStream zipStream = new GZIPInputStream(fileStream);
            ObjectInputStream objectStream = new ObjectInputStream(zipStream);
            try
            {
                while (true)
                {
                    Object obj = objectStream.readObject();
                    long key = ((Pracownik) obj).pesel;
                    data.put(key, obj);
                }
            } catch (EOFException e)
            {
                System.out.println("Przywrócono backup.");
            }
            objectStream.close();
            zipStream.close();
            fileStream.close();
        }
        else if(filename.split("\\.")[1].equals("zip"))
        {
            ZipInputStream zipStream = new ZipInputStream(fileStream);
            ObjectInputStream objectStream = new ObjectInputStream(zipStream);
            try
            {
                while (true)
                {
                    Object obj = objectStream.readObject();
                    long key = ((Pracownik) obj).pesel;
                    data.put(key, obj);
                }
            } catch (EOFException e)
            {
                System.out.println("Przywrócono backup.");
            }
            objectStream.close();
            zipStream.close();
            fileStream.close();
        }
        } catch(IOException | ClassNotFoundException ioe) {
            ioe.printStackTrace();
        }
    }
}

