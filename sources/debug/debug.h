/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:36:51 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/18 13:36:51 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <minishell.h>

void	print_parsed(t_list *parsed);
void	print_linked_lst(t_list *lst);
void	print_lexed(char **array);

static inline void* original_malloc(size_t size) {
#undef malloc
	void* result = malloc(size);
#define malloc(size) \
        ({ \
            void* ptr = original_malloc(size); \
            fprintf(stderr, "Allocated %zu bytes at %p in %s:%d\n", size, ptr, __FILE__, __LINE__); \
            ptr; \
        })
	return result;
}

static inline void original_free(void* ptr) {
#undef free
	free(ptr);
#define free(ptr) \
        ({ \
            fprintf(stderr, "Freeing memory at %p in %s:%d\n", ptr, __FILE__, __LINE__); \
            original_free(ptr); \
            ptr = NULL; \
        })
}

static inline int original_close(int fd) {
#undef close
	int result = close(fd);
#define close(fd) \
        do { \
            fprintf(stderr, "Closing file descriptor %d at %s:%d\n", fd, __FILE__, __LINE__); \
            original_close(fd); \
        } while (0)
	return result;
}

#endif
