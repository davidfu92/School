package utilityTool;


import java.io.File;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.HashMap;

import givenTools.Bencoder2;
import givenTools.BencodingException;

public class TorrentParser {

	public TorrentParser() {
		
	}
	public byte[] readTorrentFile(File torrentFile) throws IOException {
		Path pathToFile = Paths.get(torrentFile.getAbsolutePath());
		byte[] bytesInFile = null;
		try {
			bytesInFile = Files.readAllBytes(pathToFile);
		} catch (IOException fileExcpetion) {
			throw new IOException("Invalid Torrent File Input");
		}
		return bytesInFile;
	}
	
	public String getTrackerURL(byte[] metaInfo) throws UnsupportedEncodingException, BencodingException {
		String uft8MetaInfo = new String(metaInfo, "UTF-8");
		int start = uft8MetaInfo.indexOf("announce");
		int colonLoc = uft8MetaInfo.indexOf(':', start);
		int size = 0;
		try {
			size = Integer.parseInt(uft8MetaInfo.substring(start+8, colonLoc));
		}catch(NumberFormatException numException) {
			throw new BencodingException("Excpetion size of String Missing Value");
		}
		String announce = uft8MetaInfo.substring(colonLoc+1, colonLoc+size+1);
		return announce;
	}
	
	public String byteArrayToHexString(byte[] data) {
		String hashHex = "";
	  for (int i = 0; i < data.length; i++)
	  {
	  	hashHex += Integer.toString((data[i] & 0xff) + 0x100,16).substring(1);
	  }
		return hashHex;
	}
	
	public String hexToURLEncoding(String hexValue) {
		StringBuffer urlEncode = new StringBuffer();
	  for(int x = 0; x<hexValue.length(); x+=2) {
	  	String decode =hexValue.substring(x, x+2);
	  	//System.out.println(decode);
	  	switch(decode) {
	  	case "2d": urlEncode.append("-"); break;
	  	case "2e": urlEncode.append("."); break;
	  	case "30": urlEncode.append("0"); break;
	  	case "31": urlEncode.append("1"); break;
	  	case "32": urlEncode.append("2"); break;
	  	case "33": urlEncode.append("3"); break;
	  	case "34": urlEncode.append("4"); break;
	  	case "35": urlEncode.append("5"); break;
	  	case "36": urlEncode.append("6"); break;
	  	case "37": urlEncode.append("7"); break;
	  	case "38": urlEncode.append("8"); break;
	  	case "39": urlEncode.append("9"); break;
	  	case "41": urlEncode.append("A"); break;
	  	case "42": urlEncode.append("B"); break;
	  	case "43": urlEncode.append("C"); break;
	  	case "44": urlEncode.append("D"); break;
	  	case "45": urlEncode.append("E"); break;
	  	case "46": urlEncode.append("F"); break;
	  	case "47": urlEncode.append("G"); break;
	  	case "48": urlEncode.append("H"); break;
	  	case "49": urlEncode.append("I"); break;
	  	case "4a": urlEncode.append("J"); break;
	  	case "4b": urlEncode.append("K"); break;
	  	case "4c": urlEncode.append("L"); break;
	  	case "4d": urlEncode.append("M"); break;
	  	case "4e": urlEncode.append("N"); break;
	  	case "4f": urlEncode.append("O"); break;
	  	case "50": urlEncode.append("P"); break;
	  	case "51": urlEncode.append("Q"); break;
	  	case "52": urlEncode.append("R"); break;
	  	case "53": urlEncode.append("S"); break;
	  	case "54": urlEncode.append("T"); break;
	  	case "55": urlEncode.append("U"); break;
	  	case "56": urlEncode.append("V"); break;
	  	case "57": urlEncode.append("W"); break;
	  	case "58": urlEncode.append("X"); break;
	  	case "59": urlEncode.append("Y"); break;
	  	case "5a": urlEncode.append("Z"); break;
	  	case "5f": urlEncode.append("_"); break;
	  	case "61": urlEncode.append("a"); break;
	  	case "62": urlEncode.append("b"); break;
	  	case "63": urlEncode.append("c"); break;
	  	case "64": urlEncode.append("d"); break;
	  	case "65": urlEncode.append("e"); break;
	  	case "66": urlEncode.append("f"); break;
	  	case "67": urlEncode.append("g"); break;
	  	case "68": urlEncode.append("h"); break;
	  	case "69": urlEncode.append("i"); break;
	  	case "6a": urlEncode.append("j"); break;
	  	case "6b": urlEncode.append("k"); break;
	  	case "6c": urlEncode.append("l"); break;
	  	case "6d": urlEncode.append("m"); break;
	  	case "6e": urlEncode.append("n"); break;
	  	case "6f": urlEncode.append("o"); break;
	  	case "70": urlEncode.append("p"); break;
	  	case "71": urlEncode.append("q"); break;
	  	case "72": urlEncode.append("r"); break;
	  	case "73": urlEncode.append("s"); break;
	  	case "74": urlEncode.append("t"); break;
	  	case "75": urlEncode.append("u"); break;
	  	case "76": urlEncode.append("v"); break;
	  	case "77": urlEncode.append("w"); break;
	  	case "78": urlEncode.append("x"); break;
	  	case "79": urlEncode.append("y"); break;
	  	case "7a": urlEncode.append("z"); break;
	  	case "7e": urlEncode.append("~"); break;
	  	default: urlEncode.append("%"+decode); break;
	  	
	  	}
	  }
	  return urlEncode.toString();
	}
	
	public String getHashInfo(byte[] metaInfo, int piece) throws BencodingException, NoSuchAlgorithmException {
		byte[] infoDictionary = Bencoder2.getInfoBytes(metaInfo).array();
		byte[] hash_info = toSHA1(infoDictionary);
		return hexToURLEncoding(byteArrayToHexString(hash_info));
	}
	
	public static byte[] toSHA1(byte[] message) throws NoSuchAlgorithmException {
	  MessageDigest encriptMessage = null;
	  try {
	    encriptMessage = MessageDigest.getInstance("SHA-1");
	  }
	  catch(NoSuchAlgorithmException e) {
	    throw new NoSuchAlgorithmException("Fail to Encript Hash_Info Value using SHA-1");
	  } 
	  return encriptMessage.digest(message);
	}
	public static byte[] hexStringToByteArray(String s) {
	  int len = s.length();
	  byte[] data = new byte[len / 2];
	  for (int i = 0; i < len; i += 2) {
	    data[i / 2] = (byte) ((Character.digit(s.charAt(i), 16) << 4)
	               + Character.digit(s.charAt(i+1), 16));
	  }
	  return data;
	}
	public HashMap<String,ArrayList<String>> parseTracker(String tracker) {
		HashMap<String,ArrayList<String>> peerMap = new HashMap<String, ArrayList<String>>();
		tracker = tracker.substring(tracker.indexOf("d2:"));
		String[] list = tracker.split("d2:");
		for(int l=1; l<list.length; l++) {
			ArrayList<String> peerInfo = new ArrayList<String>();
			String[] temp = list[l].split(":");
			//if(temp[3].startsWith("RUBT11")) {
				peerInfo.add(temp[1]);
				peerInfo.add(temp[3]);
				peerInfo.add(temp[temp.length-1].substring(temp[temp.length-1].indexOf("porti")+5,temp[temp.length-1].indexOf("ee")));
				peerMap.put("peer"+l,peerInfo);
			//}
		}
		if(peerMap.size()==0)
			return null;
		return peerMap;
		
	}
}
