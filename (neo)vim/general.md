# General Vim / Neovim notes

## Scripting

Files sourced via :source, :runtime or automatically from runtime directories
will also show up in :scriptnames and --startuptime

## Workflows

### C++ header/source sort getters/setters

1. Sort setters on header

```vim
" Select setters
:sort
```

2. Sort getters on header

```vim
" Select getters
:sort /get/
```

Mind that getters do not return void and a regex is needed to sort from setXXX
name

3. Sort setters on source

```vim
" Serialize all functions in one line
:g/::set.*(.*)\= /,/\}/ s/$\n/@@@
" Select setters
:sort /set\=/
" Deserialize
:s/@@@/\r/g
```

4. Sort getters on source

```vim
" Serialize all functions in one line
:g/::get.*(.*)\= /,/\}/ s/$\n/@@@
" Select setters
:sort /get\=/
" Deserialize
:s/@@@/\r/g
```

### Quick Fix List refactor

QFL allows to carry out refactoring at the project level in a simple way as well
as to navigate through the different occurrences of the search patterns

1. Search word: use mappings to search a pattern inside project
Rg / Ag / VimGrep / grep / Telescope ...

2. In it we can select the occurrences we want with tab / shift-tab / or all
 at once with alt + a (only in rg)

3. To send results of to quick fix list:
    - On Rg: select desired and `<Enter>`
    - On Telescope:
        - All: `<c-q><c-q>`
        - Selected: `<M-q><M-q>`

   To display the quick fix list:: copen

4. To move through the quick fix list: `<cj> / <ck>`

```vim
" Quick Fix List custom mapping to first move in current buffer
" Take you to the next / previous occurrence within the current file and if
" not, to the next / previous one next / previous file in QFL

function! QFList(forwards)
    try
        if a:forwards
            execute ':cafter'
        else
            execute ':cbefore'
        endif
    catch
        try
            if a:forwards
                execute ':cnext'
            else
                execute ':cprev'
            endif
        catch
            echo 'No more items'
        endtry
    endtry
endfunction

nnoremap <c-j> :call QFList(1)<CR>
nnoremap <c-k> :call QFList(0)<CR>
```

5. To run a replace command on each QFL entry

```vim
:cfdo %s/pattern/newWord/gc | update
```

- `%s`: looks for the pattern in the entire file of each of the QFL files. If we
  only put s /../ .. it will only replace the occurrences in the matched lines
  (it makes more sense)
- `g`: global for each QFL
- `c`: ask before modifying
- `| update`: optional, save changes immediately (or `wa` later)
