/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 10:40:18 by vlambert          #+#    #+#             */
/*   Updated: 2019/01/30 10:46:23 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <wchar.h>
# include <stdarg.h>
# include <inttypes.h>

typedef	struct	s_options
{
	char		less;
	char		plus;
	char		space;
	char		hashtag;
	char		zero;
	char		unsign;
	int			width;
	int			precision;
	char		length;
	intmax_t	number;
	long double	doubl;
}				t_options;

typedef	struct	s_count
{
	int		len;
	int		i;
	int		written;
	int		width1;
	int		width2;
	int		temp;
}				t_count;

char			*ft_newfull(unsigned int len, t_options options);
char			*ft_ltoa_base(t_options options, char base, char maj);
char			*ft_width(char *buf, t_options options, int isnumber);
char			*ft_nbrprec(char *buf, t_options options);
void			ft_strprec(char *buf, t_options options);
char			*ft_floatprec(char *buf, t_options options, long double c);
char			*ft_plusspace(char *buf, t_options options);
char			*ft_strjoinfree(char *s1, char *s2);
char			*ft_hashtag(char *buf, t_options options,
				char base, char maj);
char			*ft_putunicode(wint_t num);
int				ft_putfloat(long double c, t_options options, int maj);
void			ft_getwidth(char *str, t_count *a, va_list ap,
				t_options *options);
void			ft_getargs(char *str, t_count *a, va_list ap,
				t_options *options);
int				ft_isintfunction(char c, va_list ap, t_options *options);
int				ft_ischarfunction(char c, va_list ap, t_options options);
int				ft_isfloatfunction(char c, va_list ap, t_options options);
int				ft_ispointfunction(char c, va_list ap, t_options options);
int				ft_iswcharfunction(char c, va_list ap, t_options options);
int				ft_iswstringfunction(char c, va_list ap, t_options options);
int				ft_isnfunction(char c, va_list ap, t_count a);
int				ft_iscolorfunction(char c, va_list ap);
int				ft_strputfree(char *buf, char c, int ch, t_options options);
void			ft_percent(char *str, t_count *a, va_list ap,
				t_options *options);

#endif
