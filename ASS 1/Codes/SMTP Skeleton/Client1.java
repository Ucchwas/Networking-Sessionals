package smtp;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
 /*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.*;
import java.net.*;
import java.util.*;
import java.util.Base64;

/**
 *
 * @author User
 */
public class Client1 {

    private static Socket s = null;
    private static BufferedReader br = null;
    private static PrintWriter pr = null;

    /*
    String mailServer = "webmail.buet.ac.bd";
        InetAddress mailHost = InetAddress.getByName(mailServer);
        InetAddress localHost = InetAddress.getLocalHost();
        Socket smtpSocket = new Socket(mailHost,25);
        BufferedReader in =  new BufferedReader(new InputStreamReader(smtpSocket.getInputStream()));
        PrintWriter pr = new PrintWriter(smtpSocket.getOutputStream(),true);
     */
    public static void main(String args[]) throws UnknownHostException, IOException {
        String mailServer = "smtp.sendgrid.net";
        InetAddress mailHost = InetAddress.getByName(mailServer);
        InetAddress localHost = InetAddress.getLocalHost();
        s = new Socket(mailHost, 25);
        br = new BufferedReader(new InputStreamReader(s.getInputStream()));
        pr = new PrintWriter(s.getOutputStream(), true);
        String ID = br.readLine();
        System.out.println(ID);
        String g = "HELO " + localHost.getHostName();
        pr.println(g);
        //from here
        System.out.println(br.readLine());
        pr.println("AUTH LOGIN");
        System.out.println(br.readLine());
        pr.println(new String(Base64.getEncoder().encode("spondon".getBytes())));
        System.out.println(br.readLine());
        pr.println(new String(Base64.getEncoder().encode("Spondon77".getBytes())));
        System.out.println(br.readLine());
        //to here 
        // not required for webmail.buet.ac.bd
        System.out.print("MAIL FROM:<");
        Scanner input1 = new Scanner(System.in);
        String str1 = input1.nextLine();
        if (str1.endsWith("@gmail.com>") || str1.endsWith("@yahoo.com>")) {
            pr.println("MAIL FROM:<" + str1);
            String w1 = br.readLine();
            System.out.println(w1);

            System.out.print("RCPT TO:<");
            Scanner input2 = new Scanner(System.in);
            String str2 = input2.nextLine();
            pr.println("RCPT TO:<" + str2);
            String w2 = br.readLine();
            System.out.println(w2);

            Scanner input3 = new Scanner(System.in);
            String str3 = input3.nextLine();

            if (str3.equalsIgnoreCase("DATA")) {
                pr.println("DATA");
                String w3 = br.readLine();
                System.out.println(w3);
                /*String s = "";
                while (true) {
                    Scanner input4 = new Scanner(System.in);
                    String str4 = input4.nextLine();
                    s = s + str4;
                    if (str4.equalsIgnoreCase(".")) {
                        pr.println(s);
                        System.out.println(s);
                        String w4 = br.readLine();
                        System.out.println(w4);
                        break;
                    }
                }*/

            } else {

            }

        }
    }
}
