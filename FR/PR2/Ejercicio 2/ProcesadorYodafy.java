import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Random;
import java.io.BufferedReader;
import java.io.PrintWriter;
import java.io.InputStreamReader;

public class ProcesadorYodafy {

	private Socket socketServicio;
	private InputStream inputStream;
	private OutputStream outputStream;
	private Random random;

	public ProcesadorYodafy(Socket socketServicio) {
		this.socketServicio=socketServicio;
		random=new Random();
	}

	void procesa(){

		byte [] datosRecibidos=new byte[1024];
		int bytesRecibidos=0;
		byte [] datosEnviar;

		try {

			inputStream=socketServicio.getInputStream();
			outputStream=socketServicio.getOutputStream();

			BufferedReader reader_buf=new BufferedReader(new InputStreamReader(inputStream));

			String peticion=new String(datosRecibidos,0,bytesRecibidos);

			String respuesta=yodaDo(peticion);
			datosEnviar=respuesta.getBytes();

			PrintWriter out_writer = new PrintWriter(outputStream, true);
			out_writer.println(respuesta);

		} catch (IOException e) {
			System.err.println("Error al obtener los flujso de entrada/salida.");
		}

	}

	private String yodaDo(String peticion) {

		String[] s = peticion.split(" ");
		String resultado="";

		for(int i=0;i<s.length;i++){
			int j=random.nextInt(s.length);
			int k=random.nextInt(s.length);
			String tmp=s[j];
			s[j]=s[k];
			s[k]=tmp;
		}
		resultado=s[0];
		for(int i=1;i<s.length;i++){
		  resultado+=" "+s[i];
		}
		return resultado;
	}
}
