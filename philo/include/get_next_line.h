/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:45:38 by afelger           #+#    #+#             */
/*   Updated: 2025/02/20 08:34:10 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif /* BUFFER_SIZE */

/**
 * Reads and returns a single line from a filedescriptor
 * If the filedescriptor does not read after use, the
 * next call will return the next line
 * @param fd	(int) a file descriptor
 * @return the string of the next line
 */
char	*get_next_line(int fd);
/**
 * Copys a string from str, puts it into str if succesfull,
 * and puts the remainder into remainder.
 * Copys from index 0 to pos
 * @param str		(char **) The string to copy from, which gets replaced
 * @param remainder	(char *) The string which will contain the remainder.
 * Cannot be longer than BUFFER_SIZE + 1
 * @param pos		(int) The last index byte to copy
 * @return 1 if successfull, 0 if io error occures
 */
int		gnl_extract_string(char **str, char **remainder, int pos);
/**
 * Handles the end of the file, replaces str with, frees remainder, replaces str
 */
void	gnl_handle_eof(char **remainder, char **str);
/**
 * Creates a remainder if remainder is NULL
 * and malloc memory for str as empty string with size 1
 */
int		gnl_setup_remainder(char **remainder, char **str);

/**
 * Concats one string to another, requres that src is the size
 * of read_size or less.
 * Input Memory will be free'd
 * @param dest		(char**) freeable string, zero terminated
 * @param src		(char*) string of size read_size
 * @param read_size	(int) length of src
 * @return (int) 
 */
int		gnl_cat_and_free(char **dest, char **src, int n);
/**
 * Counts the length of a string
 */
int		gnl_ft_strlen(char *str);
/**
 * Cleans up the strings remainder and string.
 * If any of them is NULL, this pointer will not be cleaned
 */
void	gnl_ft_cleanup(char **remainder, char **str);
/**
 * Checks if a character is in a string and puts the index in "pos"
 * @param str	(char *) the string to search in
 * @param c		(char) the character to search
 * @param pos	(int *) a pointer of an int, in which the index in str is put
 * @return 1 if c is found, 0 otherwise
 */
int		gnl_ft_has_char(char *str, char c, int *pos);

#endif /* GET_NEXT_LINE_H */
