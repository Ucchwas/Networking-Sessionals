package testclient;

import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class TestClient {

    public static void main(String[] args) throws Exception {
        String sentence;
        Socket clientSocket = new Socket("localhost", 5000);
        BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter outToServer = new PrintWriter(clientSocket.getOutputStream());
        BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        while (true) {
            sentence = inFromUser.readLine();
            outToServer.println(sentence);
            System.out.println("From Server: " + inFromServer.readLine());
            outToServer.flush();
            
        }
        
    }
}

