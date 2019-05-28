
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.Writer;

import org.apache.pdfbox.pdmodel.PDDocument;
import org.apache.pdfbox.text.PDFTextStripper;
public class Parsing {

   public static void main(String args[]) throws IOException {

      File file = new File("E:/ReferenceMapper/papers/paper16.pdf");
    
      PDDocument document;
      document = PDDocument.load(file);
     
      PDFTextStripper pdfStripper = new PDFTextStripper();

      String text;
      text = pdfStripper.getText(document);
      
      BufferedWriter bufferedWriter = null;

      File myFile = new File("E:/ReferenceMapper/papers/paper16.txt");
       
      Writer writer = new FileWriter(myFile);
      bufferedWriter = new BufferedWriter(writer);
      bufferedWriter.write(text);
      
      document.close();

   }
}