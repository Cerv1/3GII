import java.io.IOException;
import java.net.UnknownHostException;
import java.net.DatagramSocket;
import java.net.DatagramPacket;
import java.net.InetAddress;

public class YodafyClienteUDP {

    public static void main(String[] args) {

        byte[] buferEnvio = new byte[256];
        byte[] buferRecepcion = new byte[256];
        int port = 8989;
        DatagramSocket socket = null;
        DatagramPacket paquete = null;
        DatagramPacket paqueteModificado = null;
        InetAddress direccion = null;
        String fraseYodificada;

        try {
            socket = new DatagramSocket();
        } catch (IOException e) {
            System.err.println("Error de entrada/salida al abrir el socket.");
        }

        try {
            direccion = InetAddress.getByName("localhost");
        } catch (UnknownHostException e) {
            System.out.println("Error al recuperar la direccion.");
        }

        buferEnvio = "Al monte del volcan debes ir sin demora".getBytes();

        try {
            paquete = new DatagramPacket(buferEnvio, buferEnvio.length, direccion, port);
            socket.send(paquete);
            paqueteModificado = new DatagramPacket(buferRecepcion, buferRecepcion.length);
            socket.receive(paqueteModificado);
        } catch (IOException e) {
            System.err.println("Error de entrada/salida al abrir el socket.");
        }
        fraseYodificada = new String(paqueteModificado.getData());
        System.out.println("\nRecibido: " + fraseYodificada + "\n");
        socket.close();
    }
}
