import random

def generate_page_reference_string(length):
    return [random.randint(0, 9) for _ in range(length)]

def fifo(page_reference_string, num_frames):
    page_faults = 0
    frame = [-1] * num_frames
    frame_index = 0

    for page in page_reference_string:
        if page not in frame:
            page_faults += 1
            frame[frame_index] = page
            frame_index = (frame_index + 1) % num_frames
        print(f"FIFO: Page {page} -> Frame: {frame}")
    
    return page_faults

def lru(page_reference_string, num_frames):
    page_faults = 0
    frame = [-1] * num_frames
    counter = [0] * num_frames

    for i, page in enumerate(page_reference_string):
        if page not in frame:
            page_faults += 1
            if -1 in frame:
                frame[frame.index(-1)] = page
            else:
                least_recent = counter.index(min(counter))
                frame[least_recent] = page
            counter[frame.index(page)] = i
        else:
            counter[frame.index(page)] = i
        print(f"LRU: Page {page} -> Frame: {frame}")
    
    return page_faults

# Generate a random page-reference string
page_reference_string = generate_page_reference_string(20)

# Apply the string to each algorithm for varying number of page frames
num_frames_range = range(1, 8)
for num_frames in num_frames_range:
    print(f"\nNumber of Frames: {num_frames}")
    print("Page-Reference String:", page_reference_string)
    fifo_page_faults = fifo(page_reference_string, num_frames)
    lru_page_faults = lru(page_reference_string, num_frames)
    print(f"FIFO Page Faults: {fifo_page_faults}")
    print(f"LRU Page Faults: {lru_page_faults}")
