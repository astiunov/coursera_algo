import java.io.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.StringTokenizer;

public class JavaExample {

    private FastScanner in;
    private PrintWriter out;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    private List<Contact> contacts;

    public static void main(String[] args) throws IOException {
        new JavaExample().processQueries();
    }

    private Query readQuery() throws IOException {
        String type = in.next();
        int number = in.nextInt();
        if (type.equals("add")) {
            String name = in.next();
            return new Query(type, name, number);
        } else {
            return new Query(type, number);
        }
    }

    private void writeResponse(String response) {
        out.println(response);
        // Uncomment the following if you want to play with the program interactively.
        // out.flush();
    }

    private void processQuery(Query query) {
        switch (query.type) {
            case "add":
                // If we already have contact with such number, we should rewrite contact's name.
                boolean found = false;
                for (Contact contact : contacts)
                    if (contact.number == query.number) {
                        contact.name = query.name;
                        found = true;
                        break;
                    }
                // Otherwise, just add it.
                if (!found)
                    contacts.add(new Contact(query.name, query.number));
                break;
            case "del":
                for (Iterator<Contact> it = contacts.iterator(); it.hasNext(); )
                    if (it.next().number == query.number) {
                        it.remove();
                        break;
                    }
                break;
            case "find":
                String response = "empty";
                for (Contact contact : contacts)
                    if (contact.number == query.number) {
                        response = contact.name;
                        break;
                    }
                writeResponse(response);
                break;
            default:
                throw new RuntimeException("Unknown query: " + query.type);
        }
    }

    public void processQueries() throws IOException {
        contacts = new ArrayList<>();
        in = new FastScanner();
        out = new PrintWriter(new BufferedOutputStream(System.out));
        int queryCount = in.nextInt();
        for (int i = 0; i < queryCount; ++i) {
            processQuery(readQuery());
        }
        out.close();
    }

    static class Contact {
        String name;
        int number;

        public Contact(String name, int number) {
            this.name = name;
            this.number = number;
        }
    }

    static class Query {
        String type;
        String name;
        int number;

        public Query(String type, String name, int number) {
            this.type = type;
            this.name = name;
            this.number = number;
        }

        public Query(String type, int number) {
            this.type = type;
            this.number = number;
        }
    }

    static class FastScanner {
        private BufferedReader reader;
        private StringTokenizer tokenizer;

        public FastScanner() {
            reader = new BufferedReader(new InputStreamReader(System.in));
            tokenizer = null;
        }

        public String next() throws IOException {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                tokenizer = new StringTokenizer(reader.readLine());
            }
            return tokenizer.nextToken();
        }

        public int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
    }
}
