import java.io.*;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class StructBinaryDataReader {

    public static void main(String[] args) throws IOException {
        File file = new File("struct_data.dat");
        byte buff[] = new byte[112];
        BufferedInputStream bis = new BufferedInputStream(new FileInputStream(file), 112);
        bis.read(buff);
        bis.close();

        int nameLength = 0;
        while(buff[nameLength] != '\0') {
            nameLength++;
        }
        String name = new String(buff, 0, nameLength);
        Double salary = ByteBuffer.wrap(buff, 100, 8).order(ByteOrder.LITTLE_ENDIAN).getDouble();
        Integer age = ByteBuffer.wrap(buff, 108, 4).order(ByteOrder.LITTLE_ENDIAN).getInt();

        System.out.println(name);
        System.out.println(salary);
        System.out.println(age);
    }
}