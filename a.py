from re import split as resplit

#from dmoj.error import InternalError
#from dmoj.utils.unicode import utf8bytes


def check(process_, judge_output: bytes, **kwargs) -> bool:
    # Discount empty lines
 #   process_lines = list(filter(None, resplit(b'[\r\n]', utf8bytes(process_output))))
    n = int(judge_output)
    if len(process_lines) > 100:
        return False
    if len(process_lines) % 2 == 1:
        return False
    matrix = [[0] * n for i in range(n)]
    axis = False
    x = []
    y = []
    try:
        for process_line in process_lines:
            process_tokens = process_line.split()
            current_value = 0
            for process_token in process_tokens:
                # Allow mixed tokens, for lines like "abc 0.68 def 0.70"
                try:
                    process_result = int(process_token)
                except ValueError:
                    return False
                else:
                    if process_result <= current_value:
                        return False
                    if process_result > n:
                        return False
                    if axis:
                        y.append(process_result)
                    else:
                        x.append(process_result)
            if axis:
                for i in x:
                    for j in y:
                        matrix[i-1][j-1] = 1
                x = []
                y = []
                axis = False
            else:
                axis = True
        print(matrix)
        for i in range(n):
            for j in range(n):
                if matrix[i][j] == 1:
                    if i == j or i == j + 1:
                        return False
                if matrix[i][j] == 0:
                    if i != j and i != j + 1:
                        return False
    except Exception:
        return False
    return True

