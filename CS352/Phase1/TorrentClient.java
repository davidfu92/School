//Import Java Packages
import utilityTool.*;
import givenTools.BencodingException;
import givenTools.ToolKit;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.ProtocolException;
import java.net.URL;
import java.net.URLConnection;
import java.security.NoSuchAlgorithmException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;

//Initiates Class
class TorrentClient {

	public static HttpURLConnection httpRequest(String url) {
		URL tracker = null;
		try {
			tracker = new URL(url);
		} catch (MalformedURLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		URLConnection httpRequest = null;
		try {
			httpRequest = tracker.openConnection();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		HttpURLConnection http = (HttpURLConnection) httpRequest;
		try {
			http.setRequestMethod("GET");
		} catch (ProtocolException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return http;
	}

	public static String getTracker(HttpURLConnection connection) {
		int responseCode = 0;
		try {
			responseCode = connection.getResponseCode();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		BufferedReader infoReceiver = null;
		try {
			infoReceiver = new BufferedReader(new InputStreamReader(
					connection.getInputStream()));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		String curl = "";
		//System.out.println("Server Replied: " + responseCode);
		StringBuffer response = new StringBuffer();
		try {
			while ((curl = infoReceiver.readLine()) != null)
				response.append(curl);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return response.toString();
	}
	
	public static String getPeerID() {
		SimpleDateFormat format = new SimpleDateFormat("MMddyykkmmssSSS");
		Date date = new Date();	
		return format.format(date);
		
	}
	// Main Method
	public static void main(String commandLineInput[]) {
		TorrentParser parser = new TorrentParser();

		if (commandLineInput.length < 1 || commandLineInput.length > 2) {
			System.out.println("Error: No Input use -h for more Info");
			System.exit(1);
		}
		// Implements -h parameter to help User
		if(commandLineInput.length == 1) {
			if (commandLineInput[0].compareTo("-h") == 0) {
				System.out
						.println("The is a basic Client used JavaSocket to connect to a paticular server. The first arguement should be the server host name and the second arguement should be the port number between 1 to 65535. Recommendation use port above 465 to avoid conflict with pre-existing port.");
			} else {
				System.out.println("Error: No Input use -h for more Info");
			}
		} else {
			// Puts parameter into variable torrentFile and outputName
			String torrentFile = commandLineInput[0];
			String outputName = commandLineInput[1];
			File torrent = new File(torrentFile);
			byte[] fileData = null;
			try {
				fileData = parser.readTorrentFile(torrent);
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			String url = null;
			try {
				url = parser.getTrackerURL(fileData);
			} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (BencodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			//http://128.6.171.131:6969/announce?info_hash=%ff%d5%20%dd%faJ%cer%8e1%df_%20%c4%bf%b4%ecr%14%9f&peer_id=ABCDEFGHIJKLMNOPQRST&port=6881&uploaded=0&downloaded=0&left=32768
			// Check make sure port is within limitation
			String hash_info = "";
			try {
				hash_info = parser.getHashInfo(fileData, 1);
				url = url+"?info_hash="+hash_info;
			} catch (NoSuchAlgorithmException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (BencodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			HashMap<String, ArrayList<String>> peerList = null;
			System.out.println(url);
			while(peerList == null) {
				String peer_id = getPeerID();
				String trackurl = url + "&peer_id=" + peer_id +"df328&port=6881&uploaded=1&downloaded=1&left=3268&numwant=20&event=started";
				HttpURLConnection request = httpRequest(trackurl);
				String tracker = getTracker(request);
				//System.out.println(tracker);
				peerList = parser.parseTracker(tracker);
				request.disconnect();
			}
			System.out.println(peerList.entrySet());
			for(int test = 1; test<=peerList.size(); test++) {
				try {
					Peer peer1 = new Peer(peerList.get("peer"+test).get(0), peerList.get("peer"+test).get(1).getBytes("UTF-8"), hash_info.getBytes("UTF-8"), Integer.parseInt(peerList.get("peer"+test).get(2)));
					peer1.run();
				} catch (NumberFormatException | UnsupportedEncodingException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			
		}
	}
}