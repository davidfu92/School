import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.nio.ByteBuffer;


public class Peer implements Runnable{
	String Host,myID;
	int Port,attempt;
	byte[] message,peerID,infoHash;
	public Peer(String ip, byte[] peerID, byte[] infoHash, int port) {
		attempt=0;
		Host = ip;
		Port = port;
		message = new byte[]
				{ 19, 'B', 'i', 't', 'T', 'o', 'r', 'r', 'e', 'n', 't', ' ', 'p', 'r', 'o',
						't', 'o', 'c', 'o', 'l',
						// Reserved bytes
						0, 0, 0, 0, 0, 0, 0, 0,
						// Info hash placeholder
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						// Peer ID placeholder
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		
	}
	@Override
	public void run() {
		// TODO Auto-generated method stub
		try {
			//Initiates Socket Connection and all Buffers
			Socket TestSocket = new Socket(Host, Port);
			PrintWriter infoSender = new PrintWriter(TestSocket.getOutputStream(), true);
			BufferedReader infoReceiver = new BufferedReader(new InputStreamReader(TestSocket.getInputStream()));
			BufferedReader standardIn = new BufferedReader(new InputStreamReader(System.in));
			try {
				String userInput = standardIn.readLine();
				//Loops while there is still input
				while(userInput != null) {
					if(userInput.compareTo("#") == 0 || userInput.compareTo("$") == 0) {
						//Exit String is Inputted and Closes all socket and buffer
						System.out.println("Program Now Exiting");
						TestSocket.close();
						infoSender.close();
						infoReceiver.close();
						standardIn.close();
						break;
					}
					infoSender.println(handShake(infoHash, peerID));
					System.out.println("Server Replied: " + infoReceiver.readLine());
					userInput = standardIn.readLine();
				}
			} catch (IOException E) {
				System.out.println("Error: Parsing Input");
			}
		} catch (Exception E) {
			System.out.println("Error: Fail To Connect To: "+Host+" On Port: "+Port);
			//while(attempt<3) {
			//	Port++;
			//	attempt++;
			//	this.run();
			//}
		}
		
	}
	public byte[] handShake(byte[] infoHash, byte[] peerId) {
		if (infoHash == null || infoHash.length != 20)
			throw new IllegalArgumentException(
					"PeerMessage: Info hash must be 20 bytes.");
		if (peerId == null || peerId.length < 20)
			throw new IllegalArgumentException(
					"PeerMessage: Peer ID must be at least 20 bytes.");
		byte[] handshake = new byte[message.length];
		System.arraycopy(message, 0, handshake, 0,
				message.length);
		System.arraycopy(infoHash, 0, handshake, 28, 20);
		System.arraycopy(peerId, 0, handshake, 48, 20);
		return handshake;
	}
}