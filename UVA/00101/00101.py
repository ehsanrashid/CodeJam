#Regular expression module so regexs can be used as a poor mans tokenizer for the input statements.
import re

#Blocks class defines the initial setup and layout of the stacks of blocks, performs the execution of commands, and pretty printing of the current state of the stacks.
class Blocks():
    
#Initialise the Blocks instance with a list of stacks of blocks, ala: [[0], [1], [2], ... bounded by size.
    def __init__(self, size, commands):
        self.stacks = [[block] for block in xrange(size)]
        self.size = size
        self.commands = commands
        
#Pretty print the current stack/block state according to the problem brief.
    def __repr__(self):
        lines = []
        for stack in xrange(self.size):
            blocks = " ".join(str(b) for b in self.stacks[stack])
            lines.append("".join(["%2d: " % stack, blocks]))

        return "\n".join(lines)

#Find which stack a block is currently residing in.
    def __find_stack(self, block):
        for stack in xrange(self.size):
            for b in self.stacks[stack]:
                if b == block:
                    return stack

#Reset any blocks following contained in stack to their original positions.
    def __reset_stack(self, stack, block):
        blocks = self.stacks[stack]
        for b in blocks:
            self.stacks[b] = [b]

#Move a block and any followers from stack_from to stack_to via ginsu slicing.
    def __move_block(self, stack_from, stack_to, block):
        blocks = self.stacks[stack_from]
        position = blocks.index(block) 
        self.stacks[stack_from] = blocks[:position]
        self.stacks[stack_to].extend(blocks[position:])

#All commands invoke __command which handles validation of the arguments and manipulation of the source and destination stacks. Brief: Any command in which a = b or in which a and b are in the same stack of blocks is an illegal command. All illegal commands should be ignored and should have no affect on the configuration of blocks.
    def __command(self, a, b, reset_a=False, reset_b=False):
        stack_a, stack_b = self.__find_stack(a), self.__find_stack(b)

        if (a == b) or (stack_a == stack_b):
            return
        if reset_a:
            self.__reset_stack(stack_a, a)
        if reset_b:
            self.__reset_stack(stack_b, b)

        self.__move_block(stack_a, stack_b, a)

#Execute all commands in self.commands by matching the command name against a public function name, applying a and b as arguments.
    def execute(self):
        for command, a, b in self.commands:
            if (a != b):
                getattr(self, command)(a, b)

#move a onto b
    def move_onto(self, a, b):
        self.__command(a, b, reset_a=True, reset_b=True)

#move a over b
    def move_over(self, a, b):
        self.__command(a, b, reset_a=True)
    
#pile a over b
    def pile_over(self, a, b):
        self.__command(a, b, reset_b=True)
    
#pile a onto b
    def pile_onto(self, a, b):
        self.__command(a, b)

#Parser class for reading program statements from a file and tokenizing those statements into valid commands for the Blocks class.
class Parser():
#Initialise the Parser with the specified regular expression as the tokenizer.
    def __init__(self, tokenizer):
        self.tokenizer = tokenizer

#Generator for opening and scanning file_name, chunking together a statement from size until quit is encountered, at which point the statement is yeilded as a single line.
    def __scan(self, file_name):
        statement = []
        for line in open(file_name):
            if not line.startswith("quit"):
                statement.append(line.strip())
            else:
                yield " ".join(statement)            

                del statement[:]

#Tokenize a statement into Blocks instance which is initialised with a size and a list of commands consisting of method_name, and two parameters a and b
    def __tokenize(self, statement):
        size, commands = None, []
        for token in self.tokenizer.finditer(statement):
            if token.group("size"):
                size = int(token.group("size"))
            else:
                commands.append(("_".join([token.group("prefix"), token.group("suffix")]),
                                 int(token.group("a")), int(token.group("b"))))
        return Blocks(size, commands)

#Public generator for yielding the result of scanning and tokenizing a single program statement from the supplied file_name.
    def parse(self, file_name):
        for statement in self.__scan(file_name):
            yield self.__tokenize(statement)

#Open and parse the blocks_problem.txt file, executing commands and printing the resulting state for each program statement found. tokenizer is the regular expression (now we have two problems ..) for tokenizing the input lines into either a size or command tokens.
if (__name__ == "__main__"):
        tokenizer = re.compile("(?P<size>^\d+)|((?P<prefix>\w+) (?P<a>\d+) (?P<suffix>\w+) (?P<b>\d+))")
    for blocks in Parser(tokenizer).parse("00101.in"):
        blocks.execute()
        print blocks
