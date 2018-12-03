import java.io.*;
import java.net.*;

public class Server {
	// This class is a UDP Server which will recevie/store/display the data.
	// The server has it's own port number(9876) that can be used to recieved data directly from different RPI's. 
	// It will be creating a backup file(database.txt) to store the collected data.
	// Use throws Exception for any invald data received. 
	
	public static void main (String[] args) throws Exception{
	
			DatagramSocket server = new DatagramSocket(9876);// created a server with port no. 9876
			byte[] R_DATA = new byte[1024];// bytes allowed to recive (1024).
			byte[] S_DATA = new byte[1024];// bytes allowed to send (1024).
			DatagramPacket R_Packet;// server recivieing packet.
			DatagramPacket S_Packet;// sever sending packet.
			
			boolean running = true;
			InetAddress IPaddr;// IPadress of the RBI. 
			int port;// variable for port no.
			File file = new File("database.txt");// creating a notpad file to store data. 
			if (!file.exists()) {// chescking if the file already exists or not.
				file.createNewFile();// if not exists then create it.
			}
			FileWriter fw = new FileWriter(file, true);// prevents the filewriter from overwriting.
			BufferedWriter w = new BufferedWriter(fw);// use the bufferWriter to access the file and input the data. 
			try {
				while(running){// while running is true. 
					R_DATA = new byte[1024];
					S_DATA = new byte[1024];
					System.out.println("\n\n=================================================Waiting for packet==================================================");
					R_Packet = new DatagramPacket(R_DATA, R_DATA.length);// reciving the packet from the RPI3. 
					server.receive(R_Packet);// server stores the received from the RPI3.
					String msg = new String(R_Packet.getData(), 0, R_Packet.getLength());// string msg will store the recived packet from 0 to length of the packet.  
					System.out.println("RECEIVED: " + msg);// output the packet. 
					w.write(msg);// storing the data from the recived packet from RPI3 to the file (database.txt).  
					w.flush();// outputs it driectly to the hard drive. 
					System.out.println("=====================================================================================================================");
				}
			} catch (IOException e) {// if there is any wrong data recived. 
				System.out.println(e);// print the error. 
			} finally {
				w.close();// close the file. 
			}
			
			server.close();// server ends.
	
	}
}

