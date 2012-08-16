def euler11(strmatrix, op, length):
    """What is the greatest product of four numbers on the same straight line 
    in the 20 by 20 grid?"""
    def getgroups(matrix, sx, sy, x, y, length):
        definitions = [ \
            (x <= sx-length, (0, +1)),  
            (y <= sy-length, (+1, 0)),
            (x <= sx-length and y <= sy-length, (+1, +1)),
            (x >= length-1 and y <= sy-length, (+1, -1))]
        return ([matrix[y+incy*k][x+incx*k] for k in xrange(length)] \
            for condition, (incy, incx) in definitions if condition)
    process_line = lambda s: map(int, s.split())
    matrix = map(process_line, filter(bool, strmatrix.splitlines()))
    sx, sy = len(matrix[0]), len(matrix)
    gg = lambda x, y: getgroups(matrix, sx, sy, x, y, length)
    groups = flatten(starmap(gg, icross(xrange(sx), xrange(sy))))
    return max(map(lambda it: reduce(op, it), groups))
 


euler11(data.problem11, operator.mul, 4)