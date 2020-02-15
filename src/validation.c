#include "asm.h"

char	*help_check_name_or_comment_champs(t_asm_content *content, int fd)
{
	char *temp;

	temp = "\0";
	do {
		temp = ft_strjoin(temp, content->line);
		ft_strdel(&content->line);
		if (parse(temp, PATTERN_NAME_CHAMPS))
		{
			if (content->flag_name == 1 || strlen(temp) > PROG_NAME_LENGTH)
				return (NULL);
			content->flag_name = 1;
			return (temp);
		}
		else if (parse(temp, PATTERN_COMMENT_CHAMPS))
		{
			if (content->flag_comment == 1 || strlen(temp) > COMMENT_LENGTH)
				return (NULL);
			content->flag_comment = 1;
			return (temp);
		}
		temp = ft_strjoin(temp, "\n");
	} while (get_next_line(fd, &content->line) > 0);
	return (NULL);
}

char	*rebase_str_first_case(char *content)
{
	char *result;
    char *str_cat;
	char *temp;
    char *temp1;
	
	result = NULL;
    str_cat = NULL;
	temp = NULL;
    temp1 = NULL;
	temp = ft_strchr(content, 37);
    temp1 = ft_strsub(content, 0, strlen(content) - strlen(temp));
    str_cat = ft_strjoin(temp1, ",");
    result = ft_strjoin(str_cat, temp);
    ft_strdel(&temp1);
    ft_strdel(&str_cat);
	return (result);
}

char	*rebase_str_second_case(char *content)
{
	char *result;
    char *str_cat;
	char *temp;
    char *temp1;
	
	result = NULL;
    str_cat = NULL;
	temp = NULL;
    temp1 = NULL;
	temp = ft_strchr(content, 58) + 1;
    temp1 = ft_strsub(content, 0, strlen(content) - strlen(temp));
    str_cat = ft_strjoin(temp1, ",");
    result = ft_strjoin(str_cat, temp);
    ft_strdel(&temp1);
    ft_strdel(&str_cat);
	return (result);
}

char	*help_validation(char *content)
{
	if (parse(content, PATTERN_HELP_VALIDATION_FIRST_CASE))
		content = rebase_str_first_case(content);
	if (parse(content, PATTERN_HELP_VALIDATION_SECOND_CASE))
		content = rebase_str_second_case(content);
	return (content);
}

char	*check_valid(t_asm_content *content, int fd)
{
	if (parse(content->line, PATTERN_SPACE_OR_EMPTY_LINE)){
		return (content->line);
	}
	else if (parse(content->line, PATTERN_NAME_OR_COMMENT_CHAMPS_FIRST_STAGE))
		return (help_check_name_or_comment_champs(content, fd));
	else if (parse(content->line, PATTERN_COMMENT))
	{
		return (content->line);
	}
	else if (content->flag_name && content->flag_comment && parse(content->line, PATTERN))
	{
		content->flag_pattern = 1;
		content->line = help_validation(content->line);
		// printf("%s\n", content->line);
		return (content->line);
	}
	return (NULL);
}

char	*search_label(t_strings *rows, char *content)
{
	t_token		*pointer;
	t_strings	*struct_pointer;
	char		*temp;
	char		*temp1;

	struct_pointer = rows;
	while (struct_pointer)
	{
		pointer = struct_pointer->string;
		while (pointer)
		{
			if (!ft_strcmp(pointer->type, LABEL_NAME) && parse(content, DIRECT_LABEL) && !ft_strcmp((temp = ft_strsub(pointer->content, 0, strlen(pointer->content) - 1)), (temp1 = ft_strsub(content, 2, strlen(content)))))
			{
				ft_strdel(&temp);
				ft_strdel(&temp1);
				return (content);
			}
			else if (!ft_strcmp(pointer->type, LABEL_NAME) && parse(content, INDIRECT_LABEL) && !ft_strcmp((temp = ft_strsub(pointer->content, 0, strlen(pointer->content) - 1)), (temp1 = ft_strsub(content, 1, strlen(content)))))
			{
				ft_strdel(&temp);
				ft_strdel(&temp1);
				return (content);
			}
			
			pointer = pointer->next;
		}
		struct_pointer = struct_pointer->next;
	}
	return (NULL);
}

char	*check_all_label(t_strings *rows, t_asm_content **struct_content)
{
	t_token		*pointer;
	t_strings	*struct_pointer;
	int			flag;

	flag = 0;
	struct_pointer = rows;
	while (struct_pointer)
	{
		pointer = struct_pointer->string;
		while (pointer)
		{
			if (!ft_strcmp(pointer->type, DIRECT_LABEL_NAME) || !ft_strcmp(pointer->type, INDIRECT_LABEL_NAME))
			{
				if (!search_label(rows, pointer->content))
					return (clean_memory_t_strings(rows));
			}
			if (!ft_strcmp(pointer->type, INSTRACTION_NAME))
			{
				if (check(pointer))
					(*struct_content)->memory_code_size += ONE_BYTE;
				if (check_t_dir_size(pointer))
					flag = 1;
				(*struct_content)->memory_code_size += ONE_BYTE;
			}
			else if (!ft_strcmp(pointer->type, REGISTER_NAME))
				(*struct_content)->memory_code_size += ONE_BYTE;
			else if (!ft_strcmp(pointer->type, INDIRECT_NAME) || !ft_strcmp(pointer->type, INDIRECT_LABEL_NAME))
				(*struct_content)->memory_code_size += TWO_BYTE;
			else if (!ft_strcmp(pointer->type, DIRECT_NAME) || !ft_strcmp(pointer->type, DIRECT_LABEL_NAME))
				(*struct_content)->memory_code_size += flag ? FOUR_BYTE : TWO_BYTE;
			pointer->memory_size = (*struct_content)->memory_code_size;
			pointer = pointer->next;
		}
		flag = 0;
		struct_pointer = struct_pointer->next;
	}
	return ("very good");
}