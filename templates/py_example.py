class Query:
    def __init__(self, query):
        self.type = query[0]
        self.number = int(query[1])
        if self.type == 'add':
            self.name = query[2]

class QueryProcessor:
    def __init__(self):
        # Keep list of all existing (i.e. not deleted yet) contacts.
        self.contacts = []
    def read_query(self):
        return Query(input().split())
    def write_response(self, response):
        print(response)
    def process_query(self, query):
        if query.type == 'add':
            # if we already have contact with such number,
            # we should rewrite contact's name
            for contact in self.contacts:
                if contact.number == query.number:
                    contact.name = query.name
                    break
            else: # otherwise, just add it
                self.contacts.append(query)
        elif query.type == 'del':
            for j in range(len(self.contacts)):
                if self.contacts[j].number == query.number:
                    self.contacts.pop(j)
                    break
        else:
            response = 'empty'
            for contact in self.contacts:
                if contact.number == query.number:
                    response = contact.name
                    break
            self.write_response(response)
    def process_queries(self):
        n = int(input())
        for i in range(n):
            self.process_query(self.read_query())

if __name__ == '__main__':
    proc = QueryProcessor()
    proc.process_queries()

