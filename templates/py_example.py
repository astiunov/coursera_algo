class Query:
    def __init__(self, query):
        self.type = query[0]
        self.number = int(query[1])
        if self.type == 'add':
            self.name = query[2]

def read_queries():
    n = int(input())
    return [Query(input().split()) for i in range(n)]

def write_responses(result):
    print('\n'.join(result))

def process_queries(data):
    result = []
    for i in range(len(data)):
        # try to find a previously processed query to add this number,
        # if found - make the corresponding name empty
        if data[i].type == 'del':
            for j in range(i):
                if data[j].type == 'add' and data[j].number == data[i].number:
                    data[j].name = 'empty'
                    break
        # try to find this number among previously processed 'add' queries
        elif data[i].type == 'find':
            cur_res = 'empty'
            for j in range(i):
                if data[j].type == 'add' and data[j].number == data[i].number:
                    cur_res = data[j].name
                    break
            result.append(cur_res)
    return result

if __name__ == '__main__':
    write_responses(process_queries(read_queries()))

