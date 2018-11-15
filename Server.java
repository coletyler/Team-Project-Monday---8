import java.io.*;
import java.net.*;

public class Server {
	
	public static void main (String[] args) throws Exception{
	
			DatagramSocket server = new DatagramSocket(9876);
			byte[] R_DATA = new byte[1024];
			byte[] S_DATA = new byte[1024];
			DatagramPacket R_Packet;
			DatagramPacket S_Packet;
			String msg;
			boolean running = true;
			InetAddress IPaddr;
			int port;
			
			while(running){
				R_DATA = new byte[1024];
				S_DATA = new byte[1024];
				System.out.println("Waiting for packet");
				R_Packet = new DatagramPacket(R_DATA, R_DATA.length);
				server.receive(R_Packet);
				//System.out.println("R_DATA String FORMAT: " + new String(R_DATA, 0));
				msg = new String(R_Packet.getData());
				System.out.println("RECEIVED: " + msg);
				if(msg.trim().toLowerCase().equals("quit")){
					System.out.println("QUIT");
					running = false;
				}
				IPaddr = R_Packet.getAddress();
				port = R_Packet.getPort();
				msg = "RECEIVED: " + msg;
				S_Packet = new DatagramPacket(msg.getBytes(), msg.getBytes().length, IPaddr, port);
				server.send(S_Packet);
			}
			
			server.close();
	
	}
}

