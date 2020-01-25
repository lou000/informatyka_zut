package com.company;
import lab_5.*;
import lab_7.*;

public class Main {
    public static void main(String args[])
    {
//        lab5_Controller lab = new lab5_Controller();
//        lab.lab_5();
//        lab7_Model lab = new lab7_Model();
//        for(int i =0; i<1000; i++)
//        {
//            Handlowiec a = new Handlowiec();
//            a.surname = "Lewicki";
//            a.pesel = 93080415532L;
//            a.job = Pracownik.Job.Handlowiec;
//            a.name = "Maciej";
//            a.pay = 9999;
//            a.provision = 20;
//            a.provision_limit = 200;
//            lab.addWorker(a.pesel, a);
//        }
//        lab.exportBackup("backup2.gzip", lab7_Model.CompressionMode.GZIP);
//        lab.removeWorker(93080415532L);
//        if(lab.getWorker(93080415532L)==null)
//            System.out.println("Nie ma pracownika.");
//        lab.importBackup("backup2.gzip");
//        if(lab.getWorker(93080415532L)==null)
//            System.out.println("Nie ma pracownika.");
        lab7_Controller lab = new lab7_Controller();
        lab.lab_7();
    }
}
