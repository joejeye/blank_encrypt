"""
This expriment verifies that a PRN generator with fixed 
taps generates PRN codes with periodicity
"""

taps = [0, 2, 5, 7]

init_seq = [1 for i in range(8)]

times_shift = 64

"""
Compute the xor of a list of binary values
"""
def xor(bit_list):
    if len(bit_list) == 1:
        return bit_list[0]
    
    return bit_list[0] ^ xor(bit_list[1:])


"""
Generate next PRN code based on the current one
"""
def OneShift(prev_seq):
    global taps
    next_bit = xor(
        [prev_seq[i] for i in taps]
    )
    out_seq = [next_bit] + prev_seq[0:len(prev_seq)-1]
    return out_seq

"""
Convert 8-bit long binary list to decimal integer
"""
def Bit8ToDec(bit_list):
    if len(bit_list) != 8:
        raise ValueError("The length of the input list must be 8")
    
    pow2s = [
        2**i for i in list(range(7,-1,-1))
    ]

    decs = [
        bit_list[i] * pow2s[i] for i in range(8)
    ]

    return sum(decs)
    



if __name__ == "__main__":
    prncode = init_seq
    for i in range(times_shift):
        print(Bit8ToDec(prncode))
        prncode = OneShift(prncode)