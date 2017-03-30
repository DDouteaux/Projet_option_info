import os, pickle
import numpy as np
from urllib.request import urlretrieve
from sys import exit

def prepare_data(seqs, labels, maxlen=None):
    """
    - Put the data into matrices
    - Pad the sequences so they are all the same lengths
    """
    n_samples = len(seqs)
    lengths = [len(s) for s in seqs]
    if maxlen is None: maxlen = max(lengths)
        
    if maxlen < 0: return None, None, None
        
    x = np.zeros((maxlen, n_samples), dtype=np.float32)
    x_mask = np.zeros((maxlen, n_samples), dtype=np.float32)
    labels = np.array(labels, dtype=np.float32)
    
    for i, seq in enumerate(seqs):
        x[:lengths[i], i] = seq
        x_mask[:lengths[i], i] = 1
    
    return x, x_mask, labels


def get_dataset_file(path, name='imdb.pkl', 
                     origin="http://www.iro.umontreal.ca/~lisa/deep/data/imdb.pkl", 
                     test_portion=0.8):
    
    '''Look for it as if it is a full path, or a local path
    otherwise download it'''
    if not os.path.isfile(path) and not 'imdb' in path:
        exit('File in path %s not found' % path)
    elif not os.path.isfile(path):
        print('Downloading %s from %s' % (name, origin))
        path, _ = urlretrieve(origin, os.path.join(os.getcwd(), name))
    else: 
        print('Found existing file', path)
    
    if path.endswith('.gz'):
        path = gzip.decompress(path)
    
    if 'imdb' in path:
        with open(path, 'rb') as f:
            train_set = pickle.load(f)
            test_set = pickle.load(f)
    else:
        with open(path, 'rb') as f:
            save = pickle.load(f)
            dictionary = save['dictionary']
            reverse_dictionary = save['reverse_dictionary']
            count = save['count']
            data = save['data']
            
            test_limit = int(np.round(len(data[0])*test_portion))
            train_set = [data[0][:test_limit], data[1][:test_limit]]
            test_set = [data[0][test_limit:], data[1][test_limit:]]
    
    return train_set, test_set


def load_data(path='imdb.pkl', n_words=100000, maxlen=None, cut_and_keep=True, 
              sort_by_len=True, valid_portion=0.1):
    """
    Load the data and clean it
    
    path : \str\       the path to the dataset if previously downloaded
    n_words : \int\    the number of words included in the vocabulary ; the rest will be UNK
    maxlen : \int\     the maximum length (inclusive) considered for the sequences
    cut_by_len : \bool\   whether to cut (or simply avoid) sequences longer than maxlen
    sort_by_len : \bool\  whether or not to sort by length to speed up padding
    valid_portion : \float\  portion of the dataset that will be in the validation set
    """
    
    ####################
    #### LOAD DATA #####
    ####################
    
    train_set, test_set = get_dataset_file(path)
    
    # we remove the sequences longer than maxlen
    def cut_maxlen(dataset):
        new_dataset_x = []
        new_dataset_y = []
        for x, y in zip(dataset[0], dataset[1]):
            if len(x) <= maxlen:
                new_dataset_x.append(x)
                new_dataset_y.append(y)
            elif cut_and_keep:
                new_dataset_x.append(x[:maxlen])
                new_dataset_y.append(y)
        return (new_dataset_x, new_dataset_y)
    
    if maxlen is not None:
        train_set = cut_maxlen(train_set)
        test_set = cut_maxlen(test_set)
        print('[Parsing] Sequences cut to maxlen = ', maxlen)
    
    # we split the training set into training and validation
    train_set_x, train_set_y = train_set
    n_samples = len(train_set_y)
    permut = np.random.permutation(n_samples)
    n_train = int(np.round(n_samples*(1 - valid_portion)))
    
    valid_set_x = [train_set_x[i] for i in permut[n_train:]]
    valid_set_y = [train_set_y[i] for i in permut[n_train:]]
    train_set_x = [train_set_x[i] for i in permut[:n_train]]
    train_set_y = [train_set_y[i] for i in permut[:n_train]]
    
    # we remove unk words (those whose number is greater than n_words)
    def remove_unk(dataset):
        return [[1 if w >= n_words else w for w in seq] for seq in dataset]
    
    test_set_x, test_set_y = test_set
    
    train_set_x = remove_unk(train_set_x)
    valid_set_x = remove_unk(valid_set_x)
    test_set_x = remove_unk(test_set_x)
    print('[Parsing] Words unk are removed')
    
    
    # we may sort by length in order to speed up padding later
    def len_argsort(seq):
        return sorted(range(len(seq)), key=lambda i: len(seq[i]))
    
    if sort_by_len:
        sorted_index = len_argsort(test_set_x)
        test_set_x = [test_set_x[i] for i in sorted_index]
        test_set_y = [test_set_y[i] for i in sorted_index]

        sorted_index = len_argsort(train_set_x)
        train_set_x = [train_set_x[i] for i in sorted_index]
        train_set_y = [train_set_y[i] for i in sorted_index]

        sorted_index = len_argsort(valid_set_x)
        valid_set_x = [valid_set_x[i] for i in sorted_index]
        valid_set_y = [valid_set_y[i] for i in sorted_index]
        print('[Parsing] Sequences sorted by length')
    
    train = (train_set_x, train_set_y)
    valid = (valid_set_x, valid_set_y)
    test = (test_set_x ,test_set_y)
        
    return train, valid, test