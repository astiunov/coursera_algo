import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class JavaExample {
    public static void main(String[] args) {
        // First, read all queries.
        List<Query> queries = readQueries();
        // Then, compute all results.
        List<String> results = processQueries(queries);
        // Finally, output the results.
        outputResults(results);
    }

    private static List<Query> readQueries() {
        Scanner in = new Scanner(System.in);
        int queryCount = in.nextInt();
        List<Query> queries = new ArrayList<>();
        for (int i = 0; i < queryCount; ++i) {
            String type = in.next();
            int number = in.nextInt();
            if (type.equals("add")) {
                String name = in.next();
                queries.add(new Query(type, name, number));
            } else {
                queries.add(new Query(type, number));
            }
        }
        return queries;
    }

    private static List<String> processQueries(List<Query> queries) {
        List<String> results = new ArrayList<>();
        // Keep list of all existing (i.e. not deleted yet) contacts.
        List<Contact> contacts = new ArrayList<>();
        for (Query query : queries) {
            if (query.type.equals("add")) {
                contacts.add(new Contact(query.name, query.number));
            } else if (query.type.equals("del")) {
                for (int i = 0; i < contacts.size(); ++i)
                    if (contacts.get(i).number == query.number) {
                        contacts.remove(i);
                        break;
                    }
            } else if (query.type.equals("find")) {
                String name = "empty";
                for (Contact contact : contacts)
                    if (contact.number == query.number) {
                        name = contact.name;
                        break;
                    }
                results.add(name);
            }
        }
        return results;
    }

    private static void outputResults(List<String> results) {
        for (String result : results) {
            System.out.println(result);
        }
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
}
